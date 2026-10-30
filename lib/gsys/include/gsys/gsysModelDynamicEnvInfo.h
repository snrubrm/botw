#pragma once

#include <basis/seadTypes.h>
#include <hostio/seadHostIONode.h>

namespace sead {
class Heap;
}

namespace agl::lght {
class LocalLightMapObj;
}

namespace gsys {

// Native table 0x71024ca050 starts with Node::getNodeClassType and then D1/D0.
class ModelDynamicEnvInfo : public sead::hostio::Node {
public:
    ModelDynamicEnvInfo();
    virtual ~ModelDynamicEnvInfo();

    // inline-only in the original; name is a guess: ModelNW and ModelDrawObj
    // getReferenceLocalLightMapObj both read this reference at +0x10.
    const agl::lght::LocalLightMapObj* getReferenceLocalLightMapObj() const { return mReference; }
    // 0x7100c01590: returns the flag; known callers ignore the inferred bool result.
    bool setReferenceLocalLightMapObj(const agl::lght::LocalLightMapObj* obj, bool flag);
    // 0x7100c01520
    bool createLocalLightMapObj(sead::Heap* heap);

private:
    agl::lght::LocalLightMapObj* mOwned;
    const agl::lght::LocalLightMapObj* mReference;
    u8 _18;
    u8 _19;
};

}  // namespace gsys
