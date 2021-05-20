#pragma once

#include "global.h"
#include "utils/math.h"
#include <string>
#include <map>

SK_BEGIN_NAMESPACE

class Shader;
class Program;
class Material
{
private:
    struct Property
    {
        enum class Type
        {
            Matrix,
            Vector,
            Color,
            Float,
            Int,
            Texture,
        };

        union Data
        {
            float matrix[16];
            float vector[4];
            float color[4];
            float floatValue;
            int intValue;
            //OF_Texture texture;
        };

        std::string name;
        Type type;
        Data data;
        //std::shared_ptr<TextureWrapper> texture;
        //bool useOFTexture;
    };

public:
    void setMatrix(const std::string& name, const Matrix4& mat);

    void setShader(Shader* shader) { _shader = shader; }
    Shader* getShader() { return _shader; }
    void applyUniform(Program* program);

private:
    template <class T>
    void setProperty(const std::string& name, const T& v, Property::Type type)
    {
        auto find = _properties.find(name);
        if (find != _properties.end())
        {
            //assert(find->second.type == type);

            memcpy(&find->second.data, &v, sizeof(T));
        }
        else
        {
            Property p;
            p.name = name;
            p.type = type;
            memset(&p.data, 0, sizeof(p.data));
            memcpy(&p.data, &v, sizeof(T));

            _properties.insert({ name, p });
        }
    }

private:
    std::map<std::string, Property> _properties;
    Shader* _shader;
};

SK_END_NAMESPACE