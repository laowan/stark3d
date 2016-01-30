#include "loader.h"
#include "lib3ds.h"

#include <fstream>
using namespace std;

SK_BEGIN_NAMESPACE

void FileLoader3DS::load(const std::string& file)
{
    Lib3dsFile* model = lib3ds_file_open(file.c_str());
    if (!model)
        return;
}


SK_END_NAMESPACE
