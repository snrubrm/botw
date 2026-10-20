#pragma once

#include <basis/seadTypes.h>
#include <hostio/seadHostIONode.h>
#include <utility/aglDebugTexturePage.h>

namespace sead {
class Heap;
}

namespace agl {
class DrawContext;
}

namespace gsys {
class Model;
class ModelSceneConfig;
class ModelSceneContext;
}

namespace gsys {

// Base class of the sub-objects of a ModelScene (the env, ...). Partial: the constructor (0x7100c19b4c) clears +0x8
// and constructs an agl::utl::DebugTexturePage at +0x10; the derived classes' own members start at +0x250
// (ModelSceneEnv::ModelSceneEnv, 0x7100c21f8c), so the page is assumed to end there. Not modelled yet.
class ModelSceneComponent : public sead::hostio::Node {
public:
    ModelSceneComponent();
    virtual ~ModelSceneComponent();

    void setUpComponent(int, sead::Heap*, sead::Heap*);
    // 0x7100c19c0c: stores the config pointer at +0x08.
    void initializeComponent(const ModelSceneConfig* config, sead::Heap* heap);

    // Default virtuals (4 bytes each): the base component does nothing.
    virtual void bind();
    virtual void unbind(Model*);
    virtual void preCalcView(ModelSceneContext*);
    virtual void calcViewGPU(const ModelSceneContext&);
    virtual void attachHostIO(sead::hostio::Node*);
    // 0x7100c19c58: the base component draws no debug output.
    virtual void drawDebug(agl::DrawContext*, const ModelSceneContext&) const;

protected:
    /* 0x08 */ const ModelSceneConfig* _8 = nullptr;
    /* 0x10 */ agl::utl::DebugTexturePage mDebugTexturePage;
};
static_assert(sizeof(ModelSceneComponent) == 0x250);

}  // namespace gsys
