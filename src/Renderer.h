#pragma once

#include "pch.h"

struct RendererColor
{
    unsigned char R, G, B;

    RendererColor(unsigned char r = 255, unsigned char g = 255, unsigned char b = 255)
        : R(r), G(g), B(b) {}
};

struct RendererGradientColor
{
public:
    void AddColor(double location, const RendererColor& color)
    {
        locations.push_back(location);
        colors.push_back(color);
    }

    const std::vector<double>& GetLocations() const
    {
        return locations;
    }

    const std::vector<RendererColor>& GetColors() const
    {
        return colors;
    }

private:
    std::vector<double> locations;
    std::vector<RendererColor> colors;
};

class Renderer
{
public:
    Renderer()
        : m_FrameBuffer(nullptr), m_ZBuffer(nullptr), isInit(false) {}
    ~Renderer();

    void Init(int width, int height);

    // Getters
    bool IsInit() const;
    int GetWidth() const;
    int GetHeight() const;
    double GetAspectRation() const;
    RendererColor GetPixel(int x, int y) const;
    unsigned char* GetFrameBuffer();

    // Setters
    void SetWidth(int width);
    void SetHeight(int height);

    // Draw methods
    void DrawBackground(const RendererColor& color);
    void DrawBackground(const RendererGradientColor& gradient);
    void DrawPixel(int x, int y, const RendererColor& color);
    void DrawPixel(int x, int y, const RendererColor& color, int thickness);
    void DrawLine(const Vec4& p0, const Vec4& p1, const RendererColor& color, int thickness);

private:
    void setAspectRatio();
    void initBuffers();
    void initFrameBuffer();
    void initZBuffer();
    void destroyBuffers();

private:
    int m_Width;
    int m_Height;
    double m_AspectRatio;
    unsigned char* m_FrameBuffer;
    double* m_ZBuffer;

    bool isInit;
};