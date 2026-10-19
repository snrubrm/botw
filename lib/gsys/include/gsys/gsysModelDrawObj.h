#pragma once

#include <basis/seadTypes.h>
#include <heap/seadHeap.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>

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
    // 0x7100c00af4: sets the two s32 fields and the byte at +0x08 to 1. initialize 0x7100c00c94
    // reads +0x00 (a 0x20-byte record stride) and the flag at +0x08.
    struct CreateArg {
        CreateArg();
        s32 _0;
        s32 _4;
        bool _8;
        u8 _9[3];
    };
    static_assert(sizeof(CreateArg) == 0xc);

    ModelDrawObj();
    virtual ~ModelDrawObj();

    // 0x7100c01294 (declared only; body U): destroys `count` records, the first one by tail call.
    static void freeBuffer(ModelDrawObj* array, int count);
    // 0x7100c00c94 (declared only; body U): initializes `count` records in `array`.
    static void initialize(ModelDrawObj* array, int count, const CreateArg& arg, sead::Heap* heap);

    agl::lght::LocalLightMapObj* getReferenceLocalLightMapObj() const;
    // 0x7100c01468 (declared only; body U): forwards to the environment info when present.
    void setReferenceLocalLightMapObj(const agl::lght::LocalLightMapObj* obj);

private:
    u8 _8[0x0a - 0x08];
    // Instance flag byte; EffectModelDrawUnit::addInstance sets bit 1.
    u8 _a;
    u8 _b[0x12 - 0x0b];
    // Instance parameter stored by EffectModelDrawUnit::addInstance.
    u16 _12;
    u8 _14[0xb0 - 0x14];
    // Per-instance transform and position written by EffectModelDrawUnit::addInstance.
    sead::Matrix34f mMatrix;
    sead::Vector3f mPosition;
    u8 _ec[0x128 - 0xec];
    ModelDynamicEnvInfo* mDynamicEnvInfo;
};
static_assert(sizeof(ModelDrawObj) == 0x130);

}  // namespace gsys
