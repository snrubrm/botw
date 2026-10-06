#pragma once

#include <basis/seadTypes.h>
#include <hostio/seadHostIONode.h>

namespace sead {
class Heap;
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

protected:
    /* 0x08 */ void* _8;
    /* 0x10 */ u8 _10[0x250 - 0x10];
};
static_assert(sizeof(ModelSceneComponent) == 0x250);

}  // namespace gsys
