#include "learnsomething.h"

#ifdef LEARN_SDF
#include <iostream>
#include "utils/utils.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#define SDF_IMPLEMENTATION
#include "sdf.h"

#include "ft2build.h"
#include FT_FREETYPE_H
#include FT_STROKER_H

void LearnSdf()
{
    const char* fontPath = "../res/signika-regular.ttf";

    FT_Library ftLib;
    if (FT_Init_FreeType(&ftLib)) return;

    FT_Face face;
    if (FT_New_Face(ftLib, fontPath, 0, &face)) return;

    if (FT_Select_Charmap(face, FT_ENCODING_UNICODE)) return;

    int fontSize = 30;
    int dpi = 72;
    int fontSizePoints = (int)(64.f * fontSize);
    if (FT_Set_Char_Size(face, fontSizePoints, fontSizePoints, dpi, dpi)) return;

    unsigned char* buffer = NULL;
    int rows = 0;
    int width = 0;

    if (FT_Load_Char(face, 65, FT_LOAD_RENDER | FT_LOAD_NO_AUTOHINT) == 0)
    {
        buffer = face->glyph->bitmap.buffer;
        rows = face->glyph->bitmap.rows;
        width = face->glyph->bitmap.width;
        stbi_write_bmp("a.bmp", width, rows, 1, buffer);
    }

    int x, y, n;
    unsigned char *data = stbi_load("a.bmp", &x, &y, &n, 1);
 
    x = width;
    y = rows;
    unsigned char* sdf_data = makeDistanceMap(buffer, x, y, 3);
    stbi_write_bmp("aa.bmp", x + 2 * 3, y + 2 * 3, 1, sdf_data);
    stbi_write_png("a.png", x + 2 * 3, y + 2 * 3, 1, sdf_data, x + 2 * 3);

    free(sdf_data);
 
    stbi_image_free(data);

    FT_Done_Face(face);
    FT_Done_FreeType(ftLib);
}

#endif