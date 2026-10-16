#pragma once

#include <hostio/seadHostIONode.h>
#include <thread/seadAtomic.h>

namespace nn::g3d {
class ResModel;
}

namespace gsys {
class ModelResource;
class G3dResMaterialEx;
class G3dResShapeEx;

// Resource factory C0AB10 allocates 0x3f0-byte records. Native table 24D0BB0
// has Node::getNodeClassType followed by this class's own D1/D0.
class G3dResModelEx : public sead::hostio::Node {
public:
    G3dResModelEx();
    virtual ~G3dResModelEx();

    // Inline-only in the original; name is a guess. C6DD78 stores the resource;
    // independent C6F3CC formats its name and callback 1200AC0 reads it.
    const nn::g3d::ResModel* getResModel() const { return mResModel; }

    // C6E7F0 / C6E808: relaxed increment / decrement of the word at +0x3e0;
    // ClusteredRenderer 124474C releases its region model with the decrement.
    void countUpReferenceCounter();
    void countDownReferenceCounter();

private:
    ModelResource* mResource;
    nn::g3d::ResModel* mResModel;
    G3dResMaterialEx* mMaterials;
    G3dResShapeEx* mShapes;
    u8 _28[0x3e0 - 0x28];
    sead::Atomic<s32> mReferenceCounter;
    u8 _3e4[0x3f0 - 0x3e4];
};
static_assert(sizeof(G3dResModelEx) == 0x3f0);
}  // namespace gsys
