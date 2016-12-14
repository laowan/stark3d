#include "effect.h"
#include "module.h"

SK_BEGIN_NAMESPACE

void EffectNormal::render()
{
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_BLEND);

    /*
    Module::resMan().useShader("normal1");

    ShaderUniforms& uniforms = Module::resMan().currentShader()->uniforms();
    uniforms.mv = Module::sceneMan().getCamera()->getViewMat();
    uniforms.mvp = Module::sceneMan().getCamera()->getViewProjMat();
    uniforms.color = glm::vec4(1.0, 1.0, 0.0, 1.0);
    uniforms.lightPosition = glm::vec3(300.0f, 300.0f, 300.0f);
    uniforms.lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    uniforms.activeTexture = 0;

    Module::resMan().currentShader()->commitUniforms();
    */
    // now render the scene
    Module::sceneMan().render();
}

SK_END_NAMESPACE
