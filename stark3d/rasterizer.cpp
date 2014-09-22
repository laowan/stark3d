#include <cstring>
#include <cmath>
#include "rasterizer.hpp"

void
Rasterizer::setFrameBuffer(uint32_t *frameBuffer,
                           unsigned int width, unsigned int height)
{
    m_FrameBuffer = frameBuffer;
    m_Width = width;
    m_Height = height;
}

void
Rasterizer::setPixel(unsigned int x, unsigned int y, const Color &color)
{
    if(x >= m_Width || y >= m_Height)
        return;

    m_FrameBuffer[y * m_Width + x] = color.ToUInt32();
}

void
Rasterizer::setPixel(float x, float y, const Color &color)
{
    if(x < 0.0f || y < 0.0f)
        return;

    setPixel((unsigned int)x, (unsigned int)y, color);
}

void
Rasterizer::clear()
{
    memset(m_FrameBuffer, 0, sizeof(uint32_t) * m_Height * m_Width);
}

void
Rasterizer::drawLine(const Color &color1, float x1, float y1,
                     const Color &color2, float x2, float y2)
{
    float xdiff = (x2 - x1);
    float ydiff = (y2 - y1);

    if(xdiff == 0.0f && ydiff == 0.0f) {
        setPixel(x1, y1, color1);
        return;
    }

    if(fabs(xdiff) > fabs(ydiff)) {
        float xmin, xmax;

        // set xmin to the lower x value given
        // and xmax to the higher value
        if(x1 < x2) {
            xmin = x1;
            xmax = x2;
        } else {
            xmin = x2;
            xmax = x1;
        }

        // draw line in terms of y slope
        float slope = ydiff / xdiff;
        for(float x = xmin; x <= xmax; x += 1.0f) {
            float y = y1 + ((x - x1) * slope);
            Color color = color1 + ((color2 - color1) * ((x - x1) / xdiff));
            setPixel(x, y, color);
        }
    } else {
        float ymin, ymax;

        // set ymin to the lower y value given
        // and ymax to the higher value
        if(y1 < y2) {
            ymin = y1;
            ymax = y2;
        } else {
            ymin = y2;
            ymax = y1;
        }

        // draw line in terms of x slope
        float slope = xdiff / ydiff;
        for(float y = ymin; y <= ymax; y += 1.0f) {
            float x = x1 + ((y - y1) * slope);
            Color color = color1 + ((color2 - color1) * ((y - y1) / ydiff));
            setPixel(x, y, color);
        }
    }
}