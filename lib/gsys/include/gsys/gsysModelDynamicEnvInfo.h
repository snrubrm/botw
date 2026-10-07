#pragma once

#include <hostio/seadHostIONode.h>

namespace agl::lght {
class LocalLightMapObj;
}

namespace gsys {

class ModelDynamicEnvInfo : public sead::hostio::Node {
public:
    ModelDynamicEnvInfo();
    virtual ~ModelDynamicEnvInfo();

    // inline-only in the original; name is a guess: ModelNW and ModelDrawObj
    // getReferenceLocalLightMapObj both read this reference at +0x10.
    agl::lght::LocalLightMapObj* getReferenceLocalLightMapObj() const { return mReference; }

private:
    agl::lght::LocalLightMapObj* mOwned;
    agl::lght::LocalLightMapObj* mReference;
    u8 _18;
    u8 _19;
};

}  // namespace gsys
