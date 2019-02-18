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
    gradient.AddColor(0.0, { 0.5, 0.5, 0.5 });
    gradient.AddColor(1.0, { 0.3, 0.3, 0.3 });

    m_Renderer.DrawBackground(gradient);
    drawFrameBuffer(dc);
}

void DrawPanel::OnEraseBackground(wxEraseEvent& event)
{
    // Do nothing
}

void DrawPanel::drawFrameBuffer(wxDC& dc)
{
    for (int y = 0; y < m_Renderer.GetHeight(); y++)
    {
        for (int x = 0; x < m_Renderer.GetWidth(); x++)
        {
            RendererColor rColor = m_Renderer.GetPixel(x, y);
            wxColor color((int)(255 * rColor.R), (int)(255 * rColor.G), (int)(255 * rColor.B));
            dc.SetPen(wxPen(color, 1));
            dc.DrawPoint(x, y);
        }
    }
}
