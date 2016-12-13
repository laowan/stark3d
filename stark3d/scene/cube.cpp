#include "cube.h"
#include "module.h"

SK_BEGIN_NAMESPACE

Cube::Cube()
{
    Cube(1.0);
}

Cube::Cube(double edgeLength)
{
    float vertexData[] = {
        //  position             normal             uv(texture)
        // front
        -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
         1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
                                                          
        -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
                                                          
        // back                                           
         1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
                                                          
        -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
                                                          
        //left                                            
        -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
                                                          
        -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
                                                          
        // right                                          
         1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
                                                          
         1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
                                                          
        // top                                            
        -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
         1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
                                                          
        -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
         1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
                                                          
        // bottom                                         
         1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
                                                          
        -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
         1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    };

    _triCount = sizeof(vertexData)/((3+3+2)*3*sizeof(float));
    for (size_t i = 0; i < _triCount*3; i++)
    {
        vertexData[i*8] *= float(edgeLength / 2.0);
        vertexData[i*8+1] *= float(edgeLength / 2.0);
        vertexData[i*8+2] *= float(edgeLength / 2.0);
    }

    _vb = Module::renderDev().createVertexBuffer(sizeof(vertexData), vertexData); 
}

Cube::~Cube()
{
    if (_vb)
    {
        Module::renderDev().destroyBuffer(_vb);
        _vb = 0;
    }
}

bool Cube::render(RenderAction* act)
{

    Shader* shader = Module::resMan().currentShader();
    ShaderUniforms& uniforms = shader->uniforms();
    glm::mat4 saveMvpMat = uniforms.mvp;
    glm::mat4 saveMvMat = uniforms.mv;

    uniforms.mv *= act->_modelMat.glMatrix();
    uniforms.mvp *= act->_modelMat.glMatrix(); 
    uniforms.color = act->_color;
    uniforms.activeTexture = act->_activeTexture;
    shader->commitUniforms();

    Module::renderDev().setVertexBuffer(_vb);
    
    uint32 stride(sizeof(float)*3 + sizeof(float)*3 + sizeof(float)*2);
    Module::renderDev().setVertexLayout(0, stride, 0);
    Module::renderDev().setVertexLayout(1, stride, (const void*)(3*sizeof(float)));
    Module::renderDev().setVertexLayout(2, stride, (const void*)(6*sizeof(float)));
    Module::renderDev().draw(SK::PRIM_TRIANGLES, 0, _triCount*3);

    uniforms.mvp = saveMvpMat;
    uniforms.mv = saveMvMat;
    return true;
}

SK_END_NAMESPACE
