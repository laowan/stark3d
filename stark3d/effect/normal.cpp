#include "effect.h"
#include "module.h"

SK_BEGIN_NAMESPACE

void EffectNormal::render()
{
    Module::shaderMan().use("normal");

    ShaderUniforms& uniforms = Module::shaderMan().currentShader()->uniforms();

    // calculate the mvp matrix and apply it to the shader
    uniforms.mv = Module::sceneMan().getCamera()->getViewMat();
    uniforms.mvp = Module::sceneMan().getCamera()->getViewProjMat();
    uniforms.color = glm::vec4(1.0, 1.0, 0.0, 1.0);
    uniforms.lightPosition = glm::vec3(300.0f, 300.0f, 300.0f);
    uniforms.lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    uniforms.activeTexture = 0;

    Module::shaderMan().currentShader()->commitUniforms();

    // now render the scene
    Module::sceneMan().render();
}

SK_END_NAMESPACE
