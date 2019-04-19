#include "resources.h"
#include "external/rapidjson/document.h"

#include <vector>
#include <iostream>
#include <fstream>

SK_BEGIN_NAMESPACE

namespace Gltf
{
    struct Scene 
    {
        std::string name;
        std::vector<int> nodes;

        static void ParseScenes(const rapidjson::Value& val, std::vector<Scene>& scenes)
        {
            if (val.IsArray())
            {
                scenes.resize(val.Size());
                for (int i = 0; i < val.Size(); ++i)
                {
                    const rapidjson::Value& object = val[i];
                    Scene& scene = scenes[i];

                    //glTF::Read(object, "name", scene.name);
                    //glTF::ReadArray(object, "nodes", scene.nodes);
                }
            }
        }
    };

    struct Primitive {};
    struct Mesh {};
    struct Buffer {};
    struct BufferView {};
    struct Texture {};
    struct Sampler {};
    struct Image {};
    struct Material {};
    struct Node {};
    struct Accessor {};

    struct Asset
    {
        std::vector<Scene> scenes;

        bool load(const std::string& filepath)
        {
            char* buffer = nullptr;
            std::ifstream fs(filepath.c_str(), std::ifstream::binary);
            if (fs)
            {
                fs.seekg(0, fs.end);
                int length = fs.tellg();
                fs.seekg(0, fs.beg);

                buffer = new char[length+1];
                buffer[length] = 0;
                fs.read(buffer, length);
                fs.close();
            }

            rapidjson::Document doc;
            doc.Parse(buffer);
            if (!doc.HasParseError())
            {
                for (auto i = doc.MemberBegin(); i != doc.MemberEnd(); ++i)
                {
                    if (i->name == "scenes")
                    {
                        Scene::ParseScenes(i->value, scenes);
                    }
                }
            }

            if (buffer)
            {
                delete[] buffer;
            }

            return true;
        }
    };
}

void Resources::LoadGltf(const std::string& filepath)
{
    Gltf::Asset asset;
    asset.load(filepath);
}

SK_END_NAMESPACE
