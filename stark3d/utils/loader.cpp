#include "loader.h"
#include "lib3ds.h"

#include <fstream>
using namespace std;

SK_BEGIN_NAMESPACE

FileLoader3DS::FileLoader3DS() : _model(NULL)
{
}

FileLoader3DS::~FileLoader3DS()
{
    if (_model)
        lib3ds_file_free(_model);
}

void FileLoader3DS::load(const std::string& file)
{
    _model = lib3ds_file_open(file.c_str());
    if (!_model)
        return;
}

bool FileLoader3DS::getMeshData(uint32* num, MeshData** meshes)
{
    *num = _model->nmeshes;
    *meshes = (MeshData*)malloc(_model->nmeshes * sizeof(MeshData));

    for (int i = 0; i < _model->nmeshes; i++)
    {
        Lib3dsMesh* lib3dsmesh = _model->meshes[i];
        MeshData& mesh = (*meshes)[i];

        uint32 byte_size = lib3dsmesh->nvertices * 3 * sizeof(float);
        mesh.numVertices = lib3dsmesh->nvertices;
        mesh.vertices = (float*)malloc(byte_size);
        memcpy((void*)mesh.vertices, (void*)lib3dsmesh->vertices, byte_size);
        mesh.normals = NULL;
        mesh.texcos = NULL;
        mesh.numFaces = 1;
        mesh.faces = (Facets*)malloc(sizeof(Facets));
        mesh.faces->type = 0;
        mesh.faces->num = lib3dsmesh->nfaces * 3;
        mesh.faces->index = (uint32*)malloc(mesh.faces->num * sizeof(uint32));
        
        for (unsigned short i = 0; i < lib3dsmesh->nfaces; i++)
        {
            Lib3dsFace face = lib3dsmesh->faces[i];
            mesh.faces->index[3 * i + 0] = face.index[0];
            mesh.faces->index[3 * i + 1] = face.index[1];
            mesh.faces->index[3 * i + 2] = face.index[2];
        }
    }

    return true;
}


SK_END_NAMESPACE
