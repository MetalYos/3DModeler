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

RendererColor Renderer::GetPixel(int x, int y) const
{
    if (x < 0 || x >= m_Width)  return { 0, 0, 0 };
    if (y < 0 || y >= m_Height) return { 0, 0, 0 };

    RendererColor color;
    color.R = m_FrameBuffer[x * 3 + m_Width * y * 3];
    color.G = m_FrameBuffer[x * 3 + m_Width * y * 3 + 1];
    color.B = m_FrameBuffer[x * 3 + m_Width * y * 3 + 2];

    return color;
}

unsigned char* Renderer::GetFrameBuffer()
{
    return m_FrameBuffer;
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

/*-------------------------------------- Draw Methods ---------------------------------------*/
void Renderer::DrawBackground(const RendererColor& color)
{
    int size = m_Width * m_Height;
    for (int i = 0; i < size; i++)
    {
        m_FrameBuffer[i * 3] = color.R;
        m_FrameBuffer[i * 3 + 1] = color.G;
        m_FrameBuffer[i * 3 + 2] = color.B;
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
            DrawPixel(x, y, color);

            if ((1.0 - t) < AL_DBL_EPSILON)
                index++;
        }
    }
}

void Renderer::DrawPixel(int x, int y, const RendererColor& color)
{
    if (x < 0 || x >= m_Width)  return;
    if (y < 0 || y >= m_Height) return;
    m_FrameBuffer[x * 3 + m_Width * y * 3] = color.R;
    m_FrameBuffer[x * 3 + m_Width * y * 3 + 1] = color.G;
    m_FrameBuffer[x * 3 + m_Width * y * 3 + 2] = color.B;
}

void Renderer::DrawPixel(int x, int y, const RendererColor& color, int thickness)
{
    if (thickness == 0)
        DrawPixel(x, y, color);
    else
    {
        // Draw thickness
		int startX = x;
		int endX = x;
		int startY = y;
		int endY = y;
		for (int i = thickness; i > 0; i--)
		{
			if ((startX == x) && (x - i >= 0))
				startX = x - i;
			if ((endX == x) && (x + i < m_Width))
				endX = x + i;
			if ((startY == y) && (y - i >= 0))
				startY = y - i;
			if ((endY == y) && (y + i < m_Height))
				endY = y + i;
		}

		for (int xPix = startX; xPix <= endX; xPix++)
		{
			for (int yPix = startY; yPix <= endY; yPix++)
				DrawPixel(xPix, yPix, color);
		}
    }
}

void Renderer::DrawLine(const Vec4& p0, const Vec4& p1, const RendererColor& color, int thickness)
{
    int x1 = (int)p0[0];
    int y1 = (int)p0[1];
    int x2 = (int)p1[0];
    int y2 = (int)p1[1];

    int delta_x(x2 - x1);
    // if x1 == x2, then it does not matter what we set here
    signed char const ix((delta_x > 0) - (delta_x < 0));
    delta_x = std::abs(delta_x) << 1;
 
    int delta_y(y2 - y1);
    // if y1 == y2, then it does not matter what we set here
    signed char const iy((delta_y > 0) - (delta_y < 0));
    delta_y = std::abs(delta_y) << 1;

    DrawPixel(x1, y1, color, thickness);
 
    if (delta_x >= delta_y)
    {
        // error may go below zero
        int error(delta_y - (delta_x >> 1));
 
        while (x1 != x2)
        {
            // reduce error, while taking into account the corner case of error == 0
            if ((error > 0) || (!error && (ix > 0)))
            {
                error -= delta_x;
                y1 += iy;
            }
            // else do nothing
 
            error += delta_y;
            x1 += ix;
 
            DrawPixel(x1, y1, color, thickness);
        }
    }
    else
    {
        // error may go below zero
        int error(delta_x - (delta_y >> 1));
 
        while (y1 != y2)
        {
            // reduce error, while taking into account the corner case of error == 0
            if ((error > 0) || (!error && (iy > 0)))
            {
                error -= delta_y;
                x1 += ix;
            }
            // else do nothing
 
            error += delta_x;
            y1 += iy;
 
            DrawPixel(x1, y1, color, thickness);
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
    int size = m_Width * m_Height * 3;
    m_FrameBuffer = new unsigned char[size];
    for (int i = 0; i < size; i++)
    {
        m_FrameBuffer[i] = 0;
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