#pragma once

#include <prim/seadBitFlag.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
}  // namespace ksys::act

namespace uking::act {

// Placeholder name (RTTI static 0x71025ae680; vtable 0x710244e820, 14 slots: RTTI, dtor, 10 more).
// Returned by DynamicActor vtable slot 159 (Enemy::_e78, created by Enemy vtable slot 178; Player
// and Horse embed one at 0x2550 / 0x1028). Derived classes: vtable 0x710244edc0 (RTTI 0x71025aea10,
// size 0x70, built inline by Enemy slot 178) and vtable 0x710244dd20 (size 0x140, ctor
// 0x71006cef7c).
// TODO: incomplete.
class Unk_71025ae680 {
    SEAD_RTTI_BASE(Unk_71025ae680)
public:
    virtual ~Unk_71025ae680();

    // FIXME: figure out return types, parameters and names
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual void m13();

    /* 0x08 */ sead::BitFlag16 _8;  // tested by DynamicActor slots 151 (bit) and 152 (mask)
    /* 0x0a */ u8 _a;
    /* 0x10 */ ksys::act::Actor* _10;
    /* 0x18 */ s32 _18;
};

}  // namespace uking::act
