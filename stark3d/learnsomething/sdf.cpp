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

/* Handy routines for converting from fixed point */
#define FT_FLOOR(X) ((X & -64) / 64)
#define FT_CEIL(X)  (((X + 63) & -64) / 64)

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

    FT_Fixed scale = face->size->metrics.y_scale;
    int _lineHeight = FT_CEIL(FT_MulFix(face->ascender - face->descender, scale));

    unsigned char* buffer = NULL;
    int rows = 0;
    int width = 0;

    if (FT_Load_Char(face, 65, FT_LOAD_RENDER | FT_LOAD_NO_AUTOHINT) == 0)
    {
        buffer = face->glyph->bitmap.buffer;
        rows = face->glyph->bitmap.rows;
        width = face->glyph->bitmap.width;
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