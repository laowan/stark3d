#ifndef UTILS_LOADER_H
#define UTILS_LOADER_H

#include "global.h"
#include <string>

SK_BEGIN_NAMESPACE

struct Vertex3DS
{
    union
    {
        float v[3];
        struct
        {
            float x;
            float y;
            float z;
        };
    };
};

struct Index3DS
{
    union
    {
        unsigned short i[3];
        struct 
        {
            unsigned short p1;
            unsigned short p2;
            unsigned short p3;
        };
    };
};

class FileLoader
{
};

class FileLoader3DS : public FileLoader
{
public:
    void load(const std::string& file);
private:
    Vertex3DS* _vertexBuf;
    Index3DS* _indexBuf;
    unsigned short _vertexNum;
    unsigned short _polygonNum;
};

SK_END_NAMESPACE

#endif
