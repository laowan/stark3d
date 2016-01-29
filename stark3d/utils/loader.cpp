#include "loader.h"

#include <fstream>
using namespace std;

#define MAINCHUNK    0x4D4D
#define MASHDATA     0x3D3D
#define OBJNAME      0x4000
#define MESH_DATA    0x4100
#define VERTEX_DATA  0x4110
#define INDEX_DATA   0x4120
#define TEXMAP_DATA  0x4140

SK_BEGIN_NAMESPACE

void FileLoader3DS::load(const std::string& file)
{
    ifstream f;
    f.open(file, ios::in | ios::binary);

    short chunk_id = 0;
    unsigned int chunk_len = 0;
    while(!f.eof())
    {
        f.read((char*)&chunk_id, 2);
        f.read((char*)&chunk_len, 4);
        switch(chunk_id)
        {
        case MAINCHUNK:
            break;
        case MASHDATA:
            break;
        case OBJNAME:
            {
                int i = 0;
                char c;
                do
                {
                    f.read(&c, 1);
                    i++;
                } while(c != '\0' && i < 20);
            }
            break;
        case MESH_DATA:
            break;
        case VERTEX_DATA: //find out the vertex data
             f.read((char*)&_vertexNum,2);
             _vertexBuf = new Vertex3DS[_vertexNum];
             for (int i = 0; i < _vertexNum; ++i)
             {
                 f.read((char*)&(_vertexBuf[i].x), sizeof(float));
                 f.read((char*)&(_vertexBuf[i].y), sizeof(float));
                 f.read((char*)&(_vertexBuf[i].z), sizeof(float));
             }
             break;
         case INDEX_DATA:
             f.read((char*)&_polygonNum, 2);
             if (_polygonNum <= 0) return;

             _indexBuf = new Index3DS[_polygonNum];
             for(int i = 0; i < _polygonNum; ++i)
             {
                 f.read((char*)&_indexBuf[i].p1, 2);
                 f.read((char*)&_indexBuf[i].p2, 2);
                 f.read((char*)&_indexBuf[i].p3, 2);
                 f.seekg(2, ios_base::cur);
             }
             break;
         case TEXMAP_DATA:
             break;
         default:
             f.seekg(chunk_len - 6, ios_base::cur);

        }
    }

    f.close();
}


SK_END_NAMESPACE
