#pragma once

#include <basis/seadTypes.h>
#include <environment/aglEnvObjBuffer.h>

namespace agl {
class DrawContext;
}

namespace gsys {

class ModelScene;
class ModelRenderContext;

// The model-scene pass callback interface of the resource editor: a vptr-only 8-byte base
// (vtable 0x71024f4a80, 14 slots). Its defaults in the original are the four-byte empty
// functions 0x7100f36448 .. 0x7100f36478, so the argument lists come from the Graphics
// overrides in the secondary vtable at 0x71024f46a0 (slot order and every used register were
// read from those functions).
class IModelScenePassCallback {
public:
    // 0x7100f2e0ac loads the environment object buffer at Graphics +0xa98 and forwards both
    // arguments to its allocate helper 0x7100f0b5b8, which stores the scene at env_obj +0x58.
    virtual void initializeModelSceneEnvObj(ModelScene* scene,
                                            agl::env::EnvObjBuffer::AllocateArg* arg);
    // 0x7100f2e0bc / 0x7100f2e0cc forward their first argument to the model-scene managers.
    virtual void bindModelScene(ModelScene* scene);
    virtual void unbindModelScene(ModelScene* scene);
    // 0x7100f2e0e4 only touches the occlusion query drawer at Graphics +0x3a8.
    virtual void clearModelSceneQueue();
    // 0x7100f30178 dispatches on the first word (0 and 1 handled); the second argument is unused
    // in that override.
    virtual void calcModelSceneFrame(s32 view, ModelRenderContext* context);
    // 0x7100f3299c dispatches on the first word, then passes the scene (it reads the render
    // buffer context at scene +0x39c8) and the render context (view index at +8) on.
    virtual void calcModelSceneCalcRenderView(s32 view, ModelScene* scene,
                                              ModelRenderContext* context);
    // 0x7100f32ad4 / 0x7100f32c04 / 0x7100f34a74 / 0x7100f34bd4 / 0x7100f34de4 all take a draw
    // context, a pass index (0x7100f32c04 switches over 0..14), the scene (+0x39c8) and the
    // render context (view index at +8, bound through ModelRenderContext::bind).
    virtual void drawModelSceneBG(agl::DrawContext* draw_context, s32 pass, ModelScene* scene,
                                  ModelRenderContext* context);
    virtual void drawModelSceneOpa(agl::DrawContext* draw_context, s32 pass, ModelScene* scene,
                                   ModelRenderContext* context);
    virtual void drawModelSceneXlu(agl::DrawContext* draw_context, s32 pass, ModelScene* scene,
                                   ModelRenderContext* context);
    virtual void drawModelScenePfx(agl::DrawContext* draw_context, s32 pass, ModelScene* scene,
                                   ModelRenderContext* context);
    virtual void drawModelSceneFinalImage(agl::DrawContext* draw_context, s32 pass,
                                          ModelScene* scene, ModelRenderContext* context);
    // 0x7100f36358 (not overridden by Graphics): empty.
    virtual void calcModelSceneGPU();
    // 0x7100f34ed4 (the +8 subobject's copy of 0x7100f34e8c) reads the view index at +8 of the
    // render context and refreshes the grid / model renderer records.
    virtual void calcModelSceneViewGPU(ModelRenderContext* context);
    // 0x7100f35f4c (Graphics' override): empty.
    virtual void resetModelSceneHostIO(ModelRenderContext* context);
};

}  // namespace gsys
