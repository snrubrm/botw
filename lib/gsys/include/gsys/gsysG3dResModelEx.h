#pragma once

#include <hostio/seadHostIONode.h>
#include <thread/seadAtomic.h>
#include "gsys/gsysG3dResMaterialEx.h"
#include "gsys/gsysG3dResShapeEx.h"
#include "gsys/gsysModelAutoAnimation.h"

namespace nn::g3d {
class ResModel;
}

namespace gsys {
class ModelResource;

// Resource factory C0AB10 allocates 0x3f0-byte records. Native table 24D0BB0
// has Node::getNodeClassType followed by this class's own D1/D0.
class G3dResModelEx : public sead::hostio::Node {
public:
    G3dResModelEx();
    virtual ~G3dResModelEx();

    // Inline-only in the original; name is a guess. C6DD78 stores the resource;
    // independent C6F3CC formats its name and callback 1200AC0 reads it.
    const nn::g3d::ResModel* getResModel() const { return mResModel; }
    // Inline-only in the original; names are guesses. ksys::tera 0x71011413b4 indexes the
    // material (+0x18, stride 0x440) and shape (+0x20, stride 0x1190) arrays.
    G3dResMaterialEx* getMaterial(s32 index) const { return &mMaterials[index]; }
    G3dResShapeEx* getShape(s32 index) const { return &mShapes[index]; }

    // C6E7F0 / C6E808: relaxed increment / decrement of the word at +0x3e0;
    // ClusteredRenderer 124474C releases its region model with the decrement.
    void countUpReferenceCounter();
    void countDownReferenceCounter();

private:
    ModelResource* mResource = nullptr;
    nn::g3d::ResModel* mResModel;
    G3dResMaterialEx* mMaterials;
    G3dResShapeEx* mShapes;
    // Constructor 0x7100c6db2c constructs this InitArg at +0x28.
    ModelAutoAnimation::InitArg mInitArg;
    sead::Atomic<s32> mReferenceCounter;
    u8 _3e4[8] = {};
    u8 _3ec[0x3f0 - 0x3ec];
};
static_assert(sizeof(G3dResModelEx) == 0x3f0);
}  // namespace gsys
