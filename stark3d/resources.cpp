#include "resources.h"
#include "external/rapidjson/document.h"

#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>

SK_BEGIN_NAMESPACE

namespace Gltf
{
    using Attributes = std::unordered_map<std::string, int>;

    struct Scene 
    {
        std::string name;
        std::vector<int> nodes;
    };

    struct Primitive
    {
        enum class Mode
        {
            Points = 0,
            Lines = 1,
            LineLoop = 2,
            LineStrip = 3,
            Triangles = 4,
            TriangleStrip = 5,
            TriangleFan = 6
        } mode = Mode::Triangles;

        int indices = -1;
        int material = -1;
        Attributes attributes;
    };

    struct Mesh
    {
        std::vector<float> wegihts;
        std::vector<Primitive> primitives;
    };

    struct Buffer
    {
        std::string uri;
        int byteLength = 0;
    };

    struct BufferView
    {
        int buffer;
        int byteOffset = 0;
        int byteLength = 0;
        int byteStride = 0;

        enum class TargetType
        {
            None = 0,
            ArrayBuffer = 34962,
            ElementArrayBuffer = 34963
        } target;
    };

    struct Texture
    {
        int sampler;
        int source;
    };

    struct Sampler
    {
        enum class MagFilter
        {
            None,
            Nearest = 9728,
            Linear = 9729
        } magFilter = MagFilter::None;

        enum class MinFilter
        {
            None,
            Nearest = 9728,
            Linear = 9729,
            NearestMipMapNearest = 9984,
            LinearMipMapNearest = 9985,
            NearestMipMapLinear = 9986,
            LinearMipMapLinear = 9987
        } minFilter = MinFilter::None;

        enum class WrappingMode
        {
            ClampToEdge = 33071,
            MirroredRepeat = 33648,
            Repeat = 10497
        };

        WrappingMode wrapS{ WrappingMode::Repeat };
        WrappingMode wrapT{ WrappingMode::Repeat };
    };

    struct Image
    {
    };

    struct Material
    {
    };

    struct Node
    {
        int mesh;
        int camera;
        int skin;
        std::vector<int> children;
        float matrix[16];
        float rotation[4];
        float scale[3];
        float translation[3];
    };

    struct Accessor
    {
        int bufferView = -1;
        int byteOffset = 0;
        bool normalized = false;
        int count;

        enum class ComponentType
        {
            Byte = 5120,
            UnsignedByte = 5121,
            Short = 5122,
            UnsignedShort = 5123,
            UnsignedInt = 5125,
            Float = 5126
        } componentType;

        enum class Type 
        {
            Scalar,
            Vec2,
            Vec3,
            Vec4,
            Mat2,
            Mat3,
            Mat4
        } type;
    };

    struct Asset
    {
        std::string version;
        std::vector<Scene> scenes;
        std::vector<Node> nodes;
        std::vector<Mesh> meshes;
        std::vector<Buffer> buffers;
        std::vector<BufferView> bufferViews;
        std::vector<Accessor> accessors;

        bool loadScenes(const rapidjson::Value& val, std::vector<Scene>& scenes)
        {
            if (!val.IsArray()) return false;

            scenes.resize(val.Size());
            for (int i = 0; i < val.Size(); ++i)
            {
                const rapidjson::Value& object = val[i];
                Scene& scene = scenes[i];

                rapidjson::Value::ConstMemberIterator it = object.FindMember("nodes");
                if (it != object.MemberEnd())
                {
                    for (auto itr = it->value.Begin(); itr != it->value.End(); ++itr)
                    {
                        scene.nodes.push_back(itr->GetInt());
                    }
                }
            }
            return true;
        }

        bool loadNodes(const rapidjson::Value& val, std::vector<Node>& nodes)
        {
            if (!val.IsArray()) return false;

            nodes.resize(val.Size());
            for (int i = 0; i < val.Size(); ++i)
            {
                const rapidjson::Value& object = val[i];
                Node& node = nodes[i];

                rapidjson::Value::ConstMemberIterator it = object.FindMember("mesh");
                if (it != object.MemberEnd())
                {
                    node.mesh = it->value.GetInt();
                }
            }
            return true;
        }

        bool loadMeshes(const rapidjson::Value& val, std::vector<Mesh>& meshes)
        {
            if (!val.IsArray()) return false;

            meshes.resize(val.Size());
            for (int i = 0; i < val.Size(); ++i)
            {
                const rapidjson::Value& object = val[i];
                Mesh& mesh = meshes[i];

                rapidjson::Value::ConstMemberIterator it = object.FindMember("primitives");
                if (it != object.MemberEnd())
                {
                    auto& primitivesObj = it->value;
                    mesh.primitives.resize(primitivesObj.Size());
                    for (int j = 0; j < primitivesObj.Size(); ++j)
                    {
                        const rapidjson::Value& primitiveObj = primitivesObj[j];
                        Primitive& primitive = mesh.primitives[j];

                        for (auto k = primitiveObj.MemberBegin(); k != primitiveObj.MemberEnd(); ++k)
                        {
                            if (k->name == "attributes")
                            {
                                const rapidjson::Value& attributesObj = k->value;
                                for (auto m = attributesObj.MemberBegin(); m != attributesObj.MemberEnd(); ++m)
                                {
                                    primitive.attributes[m->name.GetString()] = m->value.GetInt();
                                }
                            }
                            else if (k->name == "indices")
                            {
                                primitive.indices = k->value.GetInt();
                            }
                        }
                    }
                }
            }
            return true;
        }

        bool loadBuffers(const rapidjson::Value& val, std::vector<Buffer>& buffers)
        {
            if (!val.IsArray()) return false;

            buffers.resize(val.Size());
            for (int i = 0; i < val.Size(); ++i)
            {
                const rapidjson::Value& object = val[i];
                Buffer& buffer = buffers[i];
                for (auto j = object.MemberBegin(); j != object.MemberEnd(); ++j)
                {
                    if (j->name == "uri")
                    {
                        buffer.uri = j->value.GetString();
                    }
                    else if (j->name == "byteLength")
                    {
                        buffer.byteLength = j->value.GetInt();
                    }
                }
            }
            return true;
        }

        bool loadBufferViews(const rapidjson::Value& val, std::vector<BufferView>& bufferViews)
        {
            if (!val.IsArray()) return false;

            bufferViews.resize(val.Size());
            for (int i = 0; i < val.Size(); ++i)
            {
                const rapidjson::Value& object = val[i];
                BufferView& bufferView = bufferViews[i];
                for (auto j = object.MemberBegin(); j != object.MemberEnd(); ++j)
                {
                    if (j->name == "buffer")
                    {
                        bufferView.buffer = j->value.GetInt();
                    }
                    else if (j->name == "byteOffset")
                    {
                        bufferView.byteOffset = j->value.GetInt();
                    }
                    else if (j->name == "byteLength")
                    {
                        bufferView.byteLength = j->value.GetInt();
                    }
                    else if (j->name == "target")
                    {
                        bufferView.target = static_cast<BufferView::TargetType>(j->value.GetInt());
                    }
                }
            }
            return true;
        }

        bool loadAccessors(const rapidjson::Value& val, std::vector<Accessor>& accessors)
        {
            if (!val.IsArray()) return false;

            accessors.resize(val.Size());
            for (int i = 0; i < val.Size(); ++i)
            {
                const rapidjson::Value& object = val[i];
                Accessor& accessor = accessors[i];
                for (auto j = object.MemberBegin(); j != object.MemberEnd(); ++j)
                {
                    if (j->name == "bufferView")
                    {
                        accessor.bufferView = j->value.GetInt();
                    }
                    else if (j->name == "byteOffset")
                    {
                        accessor.byteOffset = j->value.GetInt();
                    }
                    else if (j->name == "componentType")
                    {
                        accessor.componentType = static_cast<Accessor::ComponentType>(j->value.GetInt());
                    }
                    else if (j->name == "count")
                    {
                        accessor.count = j->value.GetInt();
                    }
                    else if (j->name == "type")
                    {
                        std::string typeStr = j->value.GetString();
                        if (typeStr == "SCALAR")
                        {
                            accessor.type = Accessor::Type::Scalar;
                        }
                        else if (typeStr == "VEC2") 
                        {
                            accessor.type = Accessor::Type::Vec2;
                        }
                        else if (typeStr == "VEC3") 
                        {
                            accessor.type = Accessor::Type::Vec3;
                        }
                        else if (typeStr == "VEC4") 
                        {
                            accessor.type = Accessor::Type::Vec4;
                        }
                        else if (typeStr == "MAT2") 
                        {
                            accessor.type = Accessor::Type::Mat2;
                        }
                        else if (typeStr == "MAT3") 
                        {
                            accessor.type = Accessor::Type::Mat3;
                        }
                        else if (typeStr == "MAT4") 
                        {
                            accessor.type = Accessor::Type::Mat4;
                        }
                    }
                }
            }
            return true;
        }

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
                    if (i->name == "asset")
                    {
                        rapidjson::Value::MemberIterator it = i->value.FindMember("version");
                        if (it != i->value.MemberEnd())
                        {
                            version = it->value.GetString();
                        }
                    }
                    else if (i->name == "scenes")
                    {
                        loadScenes(i->value, scenes);
                    }
                    else if (i->name == "nodes")
                    {
                        loadNodes(i->value, nodes);
                    }
                    else if (i->name == "meshes")
                    {
                        loadMeshes(i->value, meshes);
                    }
                    else if (i->name == "buffers")
                    {
                        loadBuffers(i->value, buffers);
                    }
                    else if (i->name == "bufferViews")
                    {
                        loadBufferViews(i->value, bufferViews);
                    }
                    else if (i->name == "accessors")
                    {
                        loadAccessors(i->value, accessors);
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
