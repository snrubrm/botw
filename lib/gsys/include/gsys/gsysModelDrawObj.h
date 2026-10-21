#pragma once

#include <basis/seadTypes.h>
#include <heap/seadHeap.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include "gsys/gsysModelOcclusionQuery.h"

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
    // ModelDrawObjStream::add 0x7100c7e144 copies +0x08..+0x20 and takes the address of +0x28.
    friend class ModelDrawObjStream;

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
    // The constructor zeroes +0x08, +0x0b, +0x0c, +0x10 and +0x18; the destructor skips
    // releasing +0x20 when +0x08 is non-zero.
    u16 _8;
    // Instance flag byte; EffectModelDrawUnit::addInstance sets bit 1.
    u8 _a;
    u8 _b;
    u8 _c;
    u8 _d[0x10 - 0x0d];
    u16 _10;
    // Instance parameter stored by EffectModelDrawUnit::addInstance.
    u16 _12;
    u8 _14[0x18 - 0x14];
    void* _18;
    // Released through vtable slot 1 by the destructor unless +0x08 is set.
    void* _20;
    ModelOcclusionQuery mOcclusionQuery;
    // The constructor copies sead::Vector3f::zero here and zeroes +0xac.
    sead::Vector3f _a0;
    u32 _ac;
    // Per-instance transform and position written by EffectModelDrawUnit::addInstance.
    sead::Matrix34f mMatrix;
    // The constructor initializes this to sead::Vector3f::ones.
    sead::Vector3f mPosition;
    // The constructor copies sead::Matrix34f::ident here.
    sead::Matrix34f _ec;
    u8 _11c[0x120 - 0x11c];
    void* _120;
    ModelDynamicEnvInfo* mDynamicEnvInfo;
};
static_assert(sizeof(ModelDrawObj) == 0x130);

}  // namespace gsys
