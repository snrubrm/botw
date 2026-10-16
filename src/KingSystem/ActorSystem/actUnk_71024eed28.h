#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {
class SystemGroupHandler;
}

namespace ksys::act {

// RTTI base class with vtable 0x71024eed28: D1 0x7100e9cf28 (empty), D0 0x7100e9cf2c,
// checkDerivedRuntimeTypeInfo 0x7100e9d414, getRuntimeTypeInfo 0x7100e9d484, m4 / m5 empty
// (0x7100e9d4e0 / 0x7100e9d4e4). Constructor 0x7100e9ceec; derived 0x108-byte objects are created by
// 0x710002da1c and held at Enemy + 0x12d8; Player / Enemy / NPC::m146 call sub_7100E9CF3C.
class Unk_71024eed28 {
public:
    explicit Unk_71024eed28(s32 a);
    // Declared before the RTTI functions: the destructor takes the first vtable slots.
    virtual ~Unk_71024eed28() = default;

    SEAD_RTTI_BASE(Unk_71024eed28)
public:

    virtual void m4() {}
    // Arguments from sub_7100E9CF3C, which forwards its own (`handler`: Enemy::m146 passes the first entry of
    // InstanceSet::_188).
    virtual void m5(const sead::Matrix34f& mtx, bool flag, f32 value, phys::SystemGroupHandler* handler) {}

    // 0x7100e9cf3c (placeholder name): when sUnk_71024eed20 is set, stores the translation of `mtx` in _20
    // and calls m5.
    void sub_7100E9CF3C(const sead::Matrix34f& mtx, bool flag, f32 value,
                        phys::SystemGroupHandler* handler);

    /* 0x08 */ s32 _8;
    /* 0x10 */ void* _10 = nullptr;
    /* 0x18 */ void* _18 = nullptr;
    /* 0x20 */ sead::Vector3f _20 = sead::Vector3f::zero;
    /* 0x30 */ void* _30 = nullptr;
    /* 0x38 */ bool _38 = false;
};
KSYS_CHECK_SIZE_NX150(Unk_71024eed28, 0x40);

}  // namespace ksys::act
