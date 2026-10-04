#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class Actor;

// Placeholder name (ctor 0x71006e45c4, vtable 0x710244ec58, RTTI static at GOT 0x710258fe48; 19
// slots with the destructor last). Size 0x18. Returned by Actor vtable slot 128 (DynamicActor::_a50,
// created in DynamicActor::prepareInit_; Weapon::_d90). Its functions talk to the singleton at
// GOT 0x71025793f8 (CSV GameSceneSubsys5::*).
// TODO: incomplete; parameter types of m10 are guesses.
class Unk_71006e45c4 {
    SEAD_RTTI_BASE(Unk_71006e45c4)
public:
    Unk_71006e45c4();

    /*  2 */ virtual bool m2();
    /*  3 */ virtual void m3(bool a1);
    /*  4 */ virtual bool m4();
    /*  5 */ virtual void m5(Actor* actor);
    /*  6 */ virtual void m6();
    /*  7 */ virtual void m7();
    /*  8 */ virtual void m8();
    /*  9 */ virtual bool m9();
    /* 10 */ virtual void m10(sead::Vector3f* a1, sead::Vector3f* a2);
    /* 11 */ virtual void m11();
    /* 12 */ virtual void m12();
    /* 13 */ virtual void m13();
    /* 14 */ virtual void m14();
    /* 15 */ virtual bool m15();
    /* 16 */ virtual bool m16();
    /* 17 */ virtual ~Unk_71006e45c4();

    // 0x71006e4df0 (declared only; 628 bytes): `subsys->_318` (this object) is released with `subsys->_150` and `a`.
    void sub_71006E4DF0(void* a, bool b);

    // inline-only in the original; name is a guess (the same sequence is in the destructors and in m13 / m14).
    void releaseFromScene();

    /* 0x08 */ Actor* mActor = nullptr;
    /* 0x10 */ sead::Atomic<u32> mFlags = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_71006e45c4, 0x18);

}  // namespace ksys::act
