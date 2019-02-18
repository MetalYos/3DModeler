#include "Renderer.h"

Renderer::~Renderer()
{
    destroyBuffers();
}

void Renderer::Init(int width, int height)
{
    m_Width = width;
    m_Height = height;
    setAspectRatio();

    initBuffers();

    isInit = true;
}

/*----------------------------------------- Getters -----------------------------------------*/
bool Renderer::IsInit() const
{
    return isInit;
}

int Renderer::GetWidth() const
{
    return m_Width;
}

int Renderer::GetHeight() const
{
    return m_Height;
}

double Renderer::GetAspectRation() const
{
    return m_AspectRatio;
}

const RendererColor& Renderer::GetPixel(int x, int y) const
{
    if (x < 0 || x >= m_Width)  return m_FrameBuffer[0];
    if (y < 0 || y >= m_Height) return m_FrameBuffer[0];
    return m_FrameBuffer[x + m_Width * y];
}

/*----------------------------------------- Setters -----------------------------------------*/
void Renderer::SetWidth(int width)
{
    m_Width = width;
    setAspectRatio();
    destroyBuffers();
    initBuffers();
}

void Renderer::SetHeight(int height)
{
    m_Height = height;
    setAspectRatio();
    destroyBuffers();
    initBuffers();
}

void Renderer::SetPixel(int x, int y, const RendererColor& color)
{
    if (x < 0 || x >= m_Width)  return;
    if (y < 0 || y >= m_Height) return;
    m_FrameBuffer[x + m_Width * y] = color;
}

/*-------------------------------------- Draw Methods ---------------------------------------*/
void Renderer::DrawBackground(const RendererColor& color)
{
    int size = m_Width * m_Height;
    for (int i = 0; i < size; i++)
    {
        m_FrameBuffer[i] = color;
    }
}

void Renderer::DrawBackground(const RendererGradientColor& gradient)
{
    auto locations = gradient.GetLocations();
    auto colors = gradient.GetColors();

    unsigned int index = 0;
    for (int y = 0; y < m_Height; y++)
    {
        for (int x = 0; x < m_Width; x++)
        {
            unsigned int nextIndex = (index == gradient.GetLocations().size() - 1) ? index : index + 1;
            double location0 = locations[index];
            double location1 = locations[nextIndex];
            RendererColor color0 = colors[index];
            RendererColor color1 = colors[nextIndex];

            double t = ((double)y - (location0 * m_Height)) / ((location1 * m_Height) - (location0 * m_Height));

            RendererColor color;
            color.R = color0.R * (1.0 - t) + color1.R * t;
            color.G = color0.G * (1.0 - t) + color1.G * t;
            color.B = color0.B * (1.0 - t) + color1.B * t;
            SetPixel(x, y, color);

            if ((1.0 - t) < AL_DBL_EPSILON)
                index++;
        }
    }
}

/*------------------------------------- Private Methods -------------------------------------*/
void Renderer::setAspectRatio()
{
    if (m_Height == 0) 
        m_AspectRatio = 1.0;
    else
        m_AspectRatio = (double)m_Width / (double)m_Height;
}

void Renderer::initBuffers()
{
    initFrameBuffer();
    initZBuffer();
}

void Renderer::initFrameBuffer()
{
    int size = m_Width * m_Height;
    m_FrameBuffer = new RendererColor[size];
    for (int i = 0; i < size; i++)
    {
        m_FrameBuffer[i] = { 0.0, 0.0, 0.0 };
    }
}

void Renderer::initZBuffer()
{
    int size = m_Width * m_Height;
    m_ZBuffer = new double[size];
}

void Renderer::destroyBuffers()
{
    if (m_FrameBuffer != nullptr)
        delete[] m_FrameBuffer;
    
    if (m_ZBuffer != nullptr)
        delete[] m_ZBuffer;
}