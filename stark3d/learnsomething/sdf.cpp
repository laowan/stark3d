#include "learnsomething.h"

#ifdef LEARN_SDF
#include <iostream>
#include "utils/utils.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

void LearnSdf()
{
    int x, y, n;
    unsigned char *data = stbi_load("110.bmp", &x, &y, &n, 1);

    unsigned char* sdf_data = makeDistanceMap(data, x, y, 3);
    stbi_write_bmp("1100.bmp", x + 2 * 3, y + 2 * 3, 1, sdf_data);

    stbi_image_free(data);
}

#endif