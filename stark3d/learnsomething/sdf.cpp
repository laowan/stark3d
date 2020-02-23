#include "learnsomething.h"

#ifdef LEARN_SDF
#include <iostream>
#include "utils/utils.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#include "ft2build.h"
#include FT_FREETYPE_H
#include FT_STROKER_H

void LearnSdf()
{
    const char* fontPath = "../res/American Typewriter.ttf";

    FT_Library ftLib;
    if (FT_Init_FreeType(&ftLib)) return;

    FT_Face face;
    if (FT_New_Face(ftLib, fontPath, 0, &face)) return;

    if (FT_Select_Charmap(face, FT_ENCODING_UNICODE)) return;

    int fontSize = 30;
    int dpi = 72;
    int fontSizePoints = (int)(64.f * fontSize);
    if (FT_Set_Char_Size(face, fontSizePoints, fontSizePoints, dpi, dpi)) return;

    if (FT_Load_Char(face, 48, FT_LOAD_RENDER | FT_LOAD_NO_AUTOHINT) == 0)
    {
        unsigned char* buffer = face->glyph->bitmap.buffer;
        int rows = face->glyph->bitmap.rows;
        int width = face->glyph->bitmap.width;
        stbi_write_bmp("a.bmp", width, rows, 1, buffer);

        FT_Outline _outline;
        _outline = face->glyph->outline;

        // Print outline details, taken from the glyph in the slot.
        std::cout << "\nNum points: " << _outline.n_points;
        std::cout << "\nNum contours: " << _outline.n_contours;
        std::cout << "\nContour endpoint index values:";
        for (int i = 0; i < _outline.n_contours; i++) std::cout << " " << _outline.contours[i];
        std::cout << "\n-->\n";
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ftLib);

//     int x, y, n;
//     unsigned char *data = stbi_load("110.bmp", &x, &y, &n, 1);
// 
//     unsigned char* sdf_data = makeDistanceMap(data, x, y, 3);
//     stbi_write_bmp("1100.bmp", x + 2 * 3, y + 2 * 3, 1, sdf_data);
// 
//     stbi_image_free(data);
    return;
}

#endif