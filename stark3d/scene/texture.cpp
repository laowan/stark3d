#include "texture.h"
#include "utils/bitmap.h"

SK_BEGIN_NAMESPACE

static GLenum TextureFormatForBitmapFormat(Bitmap::Format format)
{
    switch (format) {
    case Bitmap::Format_Grayscale: return GL_LUMINANCE;
    case Bitmap::Format_GrayscaleAlpha: return GL_LUMINANCE_ALPHA;
    case Bitmap::Format_RGB: return GL_RGB;
    case Bitmap::Format_RGBA: return GL_RGBA;
    default: throw std::runtime_error("Unrecognised Bitmap::Format");
    }
}

Texture::Texture(int minMagFiler, int wrapMode)
{
    init("./resource/wooden-crate.jpg", minMagFiler, wrapMode);
}

Texture::Texture(std::string file, int minMagFiler, int wrapMode)
{
    init(file, minMagFiler, wrapMode);
}

Texture::~Texture()
{
    glDeleteTextures(1, &_object);
}

void Texture::init(std::string file, int minMagFiler, int wrapMode)
{
    Bitmap bitmap = Bitmap::bitmapFromFile(file);

    glGenTextures(1, &_object);
    glBindTexture(GL_TEXTURE_2D, _object);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minMagFiler);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, minMagFiler);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
    glTexImage2D(GL_TEXTURE_2D,
        0,
        TextureFormatForBitmapFormat(bitmap.format()),
        (GLsizei)bitmap.width(),
        (GLsizei)bitmap.height(),
        0,
        TextureFormatForBitmapFormat(bitmap.format()),
        GL_UNSIGNED_BYTE,
        bitmap.pixelBuffer());
    glBindTexture(GL_TEXTURE_2D, 0);
}

bool Texture::render(RenderAction* act)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _object);
    
    act->_activeTexture = 0;
    return true;
}

SK_END_NAMESPACE
