#pragma once

#include "pch.h"

struct RendererColor
{
    double R, G, B;

    RendererColor(double r = 1.0, double g = 1.0, double b = 1.0)
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
    const RendererColor& GetPixel(int x, int y) const;

    // Setters
    void SetWidth(int width);
    void SetHeight(int height);
    void SetPixel(int x, int y, const RendererColor& color);

    // Draw methods
    void DrawBackground(const RendererColor& color);
    void DrawBackground(const RendererGradientColor& gradient);

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
    RendererColor* m_FrameBuffer;
    double* m_ZBuffer;

    bool isInit;
};