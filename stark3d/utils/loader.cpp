#include "loader.h"
//#include "lib3ds.h"

#include <fstream>
using namespace std;

SK_BEGIN_NAMESPACE

FileLoader3DS::FileLoader3DS()// : _model(NULL)
{
}

FileLoader3DS::~FileLoader3DS()
{
//     if (_model)
//         lib3ds_file_free(_model);
}

void FileLoader3DS::load(const std::string& file)
{
//     _model = lib3ds_file_open(file.c_str());
//     if (!_model)
//         return;
}

bool FileLoader3DS::getMeshData(uint32* num, MeshData** meshes)
{
//     *num = _model->nmeshes;
//     *meshes = (MeshData*)malloc(_model->nmeshes * sizeof(MeshData));
// 
//     for (int i = 0; i < _model->nmeshes; i++)
//     {
//         Lib3dsMesh* lib3dsmesh = _model->meshes[i];
//         MeshData& mesh = (*meshes)[i];
// 
//         uint32 byte_size = lib3dsmesh->nvertices * 3 * sizeof(float);
//         mesh.numVertices = lib3dsmesh->nvertices;
//         mesh.vertices = (float*)malloc(byte_size);
//         memcpy((void*)mesh.vertices, (void*)lib3dsmesh->vertices, byte_size);
// 
//         // normal
//         mesh.normals = (float*)malloc(byte_size);
//         float* face_normals = (float*)malloc(lib3dsmesh->nfaces * 3 * 3 * sizeof(float));
//         lib3ds_mesh_calculate_vertex_normals(lib3dsmesh, (float(*)[3])face_normals);
//         
//         for (unsigned short j = 0; j < lib3dsmesh->nfaces; j++)
//         {
//             for (int k = 0; k < 3; k++)
//             {
//                 unsigned short idx = lib3dsmesh->faces[j].index[k];
//                 mesh.normals[3*idx+0] = face_normals[9*j+3*k+0];
//                 mesh.normals[3*idx+1] = face_normals[9*j+3*k+1];
//                 mesh.normals[3*idx+2] = face_normals[9*j+3*k+2];
//             }
//         }
// 
//         free(face_normals);
// 
//         // texture coordinate
//         mesh.texcos = (float*)malloc(lib3dsmesh->nvertices * 2 * sizeof(float));
//         for (unsigned short j = 0; j < lib3dsmesh->nvertices; j++)
//         {
//             mesh.texcos[2*j+0] = lib3dsmesh->texcos[j][0] / (float)2.0;
//             mesh.texcos[2*j+1] = lib3dsmesh->texcos[j][1] / (float)2.0;
//         }
//         
//         mesh.numFaces = 1;
//         mesh.faces = (Facets*)malloc(sizeof(Facets));
//         mesh.faces->type = 0;
//         mesh.faces->num = lib3dsmesh->nfaces * 3;
//         mesh.faces->index = (uint32*)malloc(mesh.faces->num * sizeof(uint32));
//         
//         for (unsigned short i = 0; i < lib3dsmesh->nfaces; i++)
//         {
//             Lib3dsFace face = lib3dsmesh->faces[i];
//             mesh.faces->index[3 * i + 0] = face.index[0];
//             mesh.faces->index[3 * i + 1] = face.index[1];
//             mesh.faces->index[3 * i + 2] = face.index[2];
//         }
//     }

    return true;
}


SK_END_NAMESPACE
