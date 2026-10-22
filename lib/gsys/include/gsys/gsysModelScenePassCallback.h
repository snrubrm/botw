#pragma once

namespace gsys {

// The model-scene pass callback interface of the resource editor: a vptr-only 8-byte base
// (vtable 0x71024f4a80, 14 slots). Its defaults in the original are the four-byte empty
// functions 0x7100f36448 .. 0x7100f36478. The parameter lists are not recoverable from those
// empty bodies, so they are left empty here and no CSV row is claimed for them; a caller with
// the real arguments should extend them.
class IModelScenePassCallback {
public:
    virtual void initializeModelSceneEnvObj() {}
    virtual void bindModelScene() {}
    virtual void unbindModelScene() {}
    virtual void clearModelSceneQueue() {}
    virtual void calcModelSceneFrame() {}
    virtual void calcModelSceneCalcRenderView() {}
    virtual void drawModelSceneBG() {}
    virtual void drawModelSceneOpa() {}
    virtual void drawModelSceneXlu() {}
    virtual void drawModelScenePfx() {}
    virtual void drawModelSceneFinalImage() {}
    virtual void calcModelSceneViewGPU() {}
    virtual void resetModelSceneHostIO() {}
    virtual void calcModelSceneGPU() {}
};

}  // namespace gsys
