#pragma once

#include "pch.h"
#include "Renderer.h"

class DrawPanel : public wxPanel
{
public:
    DrawPanel(wxFrame* parent);

    void OnResize(wxSizeEvent& event);
    void OnPaint(wxPaintEvent& event);
    void OnEraseBackground(wxEraseEvent& event);

private:
    void drawFrameBuffer(wxDC& dc);

private:
    Renderer m_Renderer;
};