#pragma once

#include <basis/seadTypes.h>

namespace agl::lght {
class LocalLightMapObj;
}

namespace gsys {

class ModelDynamicEnvInfo;

// ModelDrawObj constructor 0x7100c00b04 establishes the vtable and members through +0x128.
// MassRenderer cleanup 0x71011e1788 destroys arrays with this exact 0x130-byte stride.
// The lifetime stays out of line: the original destructor 0x7100c00bcc releases its
// owned environment objects and the embedded occlusion query at +0x28.
class ModelDrawObj {
public:
    ModelDrawObj();
    virtual ~ModelDrawObj();

    // 0x7100c01294 (declared only; body U): destroys `count` records, the first one by tail call.
    static void freeBuffer(ModelDrawObj* array, int count);

    agl::lght::LocalLightMapObj* getReferenceLocalLightMapObj() const;

private:
    u8 _8[0x128 - 8];
    ModelDynamicEnvInfo* mDynamicEnvInfo;
};
static_assert(sizeof(ModelDrawObj) == 0x130);

}  // namespace gsys
