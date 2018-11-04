#ifndef UTILS_LOADER_H
#define UTILS_LOADER_H

#include "global.h"
#include <string>
class Lib3dsFile;

SK_BEGIN_NAMESPACE

typedef struct Facets
{
    uint8   type;  // 0-triangles, 1-triangle strips, 2-triangle fans
    uint32  num;
    uint32* index;
} Facets;

typedef struct MeshData
{
    uint32  numVertices;
    float*  vertices;
    float*  normals;
    float*  texcos;
    uint32  numFaces;
    Facets* faces;
} MeshData;

typedef struct Vertex3DS
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
} Vertex3DS;

typedef struct Index3DS
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
} Index3DS;

class FileLoader
{
};

class FileLoader3DS : public FileLoader
{
public:
    FileLoader3DS();
    ~FileLoader3DS();
    void load(const std::string& file);
    bool getMeshData(uint32* num, MeshData** meshes);
private:
    //Lib3dsFile* _model;
};

SK_END_NAMESPACE

#endif
