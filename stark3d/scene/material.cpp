#include "scene/material.h"
#include "graphics/program.h"

SK_BEGIN_NAMESPACE

void Material::setMatrix(const std::string& name, const Matrix4& mat)
{
    setProperty(name, mat, Property::Type::Matrix);
}

void Material::setTexture(const std::string& name, uint32 textureId)
{
    setProperty(name, textureId, Property::Type::Texture);
}

void Material::applyUniform(Program* program)
{
    for (const auto& i : _properties)
    {
        const Property& p = i.second;

        if (program->getHandle(p.name, false) != -1)
        {
            switch (p.type)
            {
            case Property::Type::Matrix:
                program->setUniformMatrix4fv(p.name, 1, GL_FALSE, (const GLfloat*)&p.data);
                break;
            case Property::Type::Vector:
            case Property::Type::Color:
                program->setUniform4fv(p.name, 1, (GLfloat*)&p.data);
                break;
            case Property::Type::Float:
                program->setUniform1f(p.name, p.data.floatValue);
                break;
            case Property::Type::Int:
                program->setUniform1i(p.name, p.data.intValue);
                break;
            case Property::Type::Texture:
                program->setUniformTexture(p.name, 0, p.data.texture);
                break;
            }
        }
    }
}

SK_END_NAMESPACE
