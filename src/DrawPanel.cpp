#include "DrawPanel.h"

DrawPanel::DrawPanel(wxFrame* parent) : wxPanel(parent)
{
    Connect(wxEVT_PAINT, wxPaintEventHandler(DrawPanel::OnPaint));
    Connect(wxEVT_ERASE_BACKGROUND, wxEraseEventHandler(DrawPanel::OnEraseBackground));
    Connect(wxEVT_SIZE, wxSizeEventHandler(DrawPanel::OnResize));
}

void DrawPanel::OnResize(wxSizeEvent& event)
{
    wxSize size = event.GetSize();
    if (!m_Renderer.IsInit())
    {
        m_Renderer.Init(size.GetWidth(), size.GetHeight());
    }
    
    m_Renderer.SetWidth(size.GetWidth());
    m_Renderer.SetHeight(size.GetHeight());
}

void DrawPanel::OnPaint(wxPaintEvent& event)
{
    wxBufferedPaintDC dc(this);

    RendererGradientColor gradient;
    gradient.AddColor(0.0, { 127, 127, 127 });
    gradient.AddColor(1.0, { 76, 76, 76 });

    m_Renderer.DrawBackground(gradient);

    double angle = 0;
    int numLines = 20;
    double radius = 300;
    RendererColor color(0, 0, 255);
    while (angle < 360)
    {
        Vec4 p1(m_Renderer.GetWidth() / 2, m_Renderer.GetHeight() / 2, 0, 0);
        Vec4 p2(m_Renderer.GetWidth() / 2 + radius * cos(ToRadians(angle)), 
                       m_Renderer.GetHeight() / 2 + radius * sin(ToRadians(angle)),
                       0, 0);
        m_Renderer.DrawLine(p1, p2, color, 3);

        angle += (360.0 / numLines);
    }

    drawFrameBuffer(dc);
}

void DrawPanel::OnEraseBackground(wxEraseEvent& event)
{
    // Do nothing
}

void DrawPanel::drawFrameBuffer(wxDC& dc)
{
    wxImage t_Image = wxImage(m_Renderer.GetWidth(), m_Renderer.GetHeight(), m_Renderer.GetFrameBuffer(), true);
    wxBitmap t_Bitmap = wxBitmap(t_Image);
    dc.DrawBitmap(t_Bitmap, 0, 0, true);
}
