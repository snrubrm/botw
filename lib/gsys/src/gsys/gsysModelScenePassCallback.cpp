#include <gsys/gsysModelScenePassCallback.h>

// 0x7100f36448 .. 0x7100f36478: every default of the interface is a four-byte empty function in
// the original (vtable 0x71024f4a80), so the out-of-line bodies are empty.
namespace gsys {

void IModelScenePassCallback::initializeModelSceneEnvObj(
    ModelScene*, agl::env::EnvObjBuffer::AllocateArg*) {}

void IModelScenePassCallback::bindModelScene(ModelScene*) {}

void IModelScenePassCallback::unbindModelScene(ModelScene*) {}

void IModelScenePassCallback::clearModelSceneQueue() {}

void IModelScenePassCallback::calcModelSceneFrame(s32, ModelRenderContext*) {}

void IModelScenePassCallback::calcModelSceneCalcRenderView(s32, ModelScene*,
                                                          ModelRenderContext*) {}

void IModelScenePassCallback::drawModelSceneBG(agl::DrawContext*, s32, ModelScene*,
                                               ModelRenderContext*) {}

void IModelScenePassCallback::drawModelSceneOpa(agl::DrawContext*, s32, ModelScene*,
                                                ModelRenderContext*) {}

void IModelScenePassCallback::drawModelSceneXlu(agl::DrawContext*, s32, ModelScene*,
                                                ModelRenderContext*) {}

void IModelScenePassCallback::drawModelScenePfx(agl::DrawContext*, s32, ModelScene*,
                                                ModelRenderContext*) {}

void IModelScenePassCallback::drawModelSceneFinalImage(agl::DrawContext*, s32, ModelScene*,
                                                       ModelRenderContext*) {}

void IModelScenePassCallback::calcModelSceneGPU() {}

void IModelScenePassCallback::calcModelSceneViewGPU(ModelRenderContext*) {}

void IModelScenePassCallback::resetModelSceneHostIO(ModelRenderContext*) {}

}  // namespace gsys
