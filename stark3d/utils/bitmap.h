#ifndef _BITMAP_H
#define _BITMAP_H

#include "global.h"
#include <string>

SK_BEGIN_NAMESPACE

class Bitmap
{
public:
    /**
    Represents the number of channels per pixel, and the order of the channels.

    Each channel is one byte (unsigned char).
    */
    enum Format {
        Format_Grayscale = 1, /**< one channel: grayscale */
        Format_GrayscaleAlpha = 2, /**< two channels: grayscale and alpha */
        Format_RGB = 3, /**< three channels: red, green, blue */
        Format_RGBA = 4 /**< four channels: red, green, blue, alpha */
    };
        
    /**
    Creates a new image with the specified width, height and format.

    Width and height are in pixels. Image will contain random garbage if
    pixels = NULL.
    */
    Bitmap(unsigned width, unsigned height, Format format, const unsigned char* pixels = NULL);
    ~Bitmap();

    /** width in pixels */
    unsigned width() const;
        
    /** height in pixels */
    unsigned height() const;
        
    /** the pixel format of the bitmap */
    Format format() const;
        
    /**
    Pointer to the raw pixel data of the bitmap.
         
    Each channel is 1 byte. The number and meaning of channels per pixel is specified
    by the `Format` of the image. The pointer points to all the columns of
    the top row of the image, followed by each remaining row down to the bottom.
    i.e. c0r0, c1r0, c2r0, ..., c0r1, c1r1, c2r1, etc
    */
    unsigned char* pixelBuffer() const;

    static Bitmap bitmapFromFile(std::string filePath);

private:
    void set(unsigned width, unsigned height, Format format, const unsigned char* pixels);

private:
    Format _format;
    unsigned _width;
    unsigned _height;
    unsigned char* _pixels;
};

SK_END_NAMESPACE

#endif
