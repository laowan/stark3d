#include "graphics/texture.h"
#include "utils/log.h"
#include "utils/gldefine.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

SK_BEGIN_NAMESPACE

Texture::Texture() : _textureId(0)
{

}

Texture::~Texture()
{
    if (_textureId)
    {
        glDeleteTextures(1, &_textureId);
        _textureId = 0;
    }
}

bool Texture::createFromFile(const std::string& path)
{
    uint8* imageData = nullptr;
    int channel = 0;
    int width, height;
    imageData = stbi_load(path.c_str(), &width, &height, &channel, 4);
    if (!imageData)
    {
        SK_LOGE("Failed to load image file.");
    }

    glGenTextures(1, &_textureId);
    glBindTexture(GL_TEXTURE_2D, _textureId);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    
    stbi_image_free(imageData);
    return true;
}

SK_END_NAMESPACE