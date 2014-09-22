#ifndef __RASTERIZER_H__
#define __RASTERIZER_H__

#include "color.hpp"

class Rasterizer
{
	protected:
		uint32_t *m_FrameBuffer;
		unsigned int m_Width, m_Height;

	public:
		void setFrameBuffer(uint32_t *frameBuffer, unsigned int width, unsigned int height);
		void setPixel(unsigned int x, unsigned int y, const Color &color = Color());
		void setPixel(float x, float y, const Color &color = Color());
		void clear();

		void drawLine(const Color &color1, float x1, float y1, const Color &color2, float x2, float y2);
};

#endif /* __RASTERIZER_H__ */