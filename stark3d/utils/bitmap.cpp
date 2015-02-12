#include "bitmap.h"

#define STBI_FAILURE_USERMSG
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

SK_BEGIN_NAMESPACE

Bitmap::Bitmap(unsigned width, unsigned height, Format format, const unsigned char* pixels /* = NULL */)
{
    _pixels = NULL;
    set(width, height, format, pixels);
}

Bitmap::~Bitmap()
{

}

unsigned int Bitmap::width() const {
    return _width;
}

unsigned int Bitmap::height() const {
    return _height;
}

Bitmap::Format Bitmap::format() const {
    return _format;
}

unsigned char* Bitmap::pixelBuffer() const {
    return _pixels;
}

Bitmap Bitmap::bitmapFromFile(std::string filePath)
{
    int width, height, channels;
    unsigned char* pixels = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
    if (!pixels) throw std::runtime_error(stbi_failure_reason());

    Bitmap bmp(width, height, (Format)channels, pixels);
    stbi_image_free(pixels);
    return bmp;
}

void Bitmap::set(unsigned width, unsigned height, Format format, const unsigned char* pixels)
{
    if (width == 0) throw std::runtime_error("Zero width bitmap");
    if (height == 0) throw std::runtime_error("Zero height bitmap");
    if (format <= 0 || format > 4) throw std::runtime_error("Invalid bitmap format");

    _width = width;
    _height = height;
    _format = format;

    size_t newSize = _width * _height * _format;
    if (_pixels){
        _pixels = (unsigned char*)realloc(_pixels, newSize);
    }
    else {
        _pixels = (unsigned char*)malloc(newSize);
    }

    if (pixels)
        memcpy(_pixels, pixels, newSize);
}

SK_END_NAMESPACE
