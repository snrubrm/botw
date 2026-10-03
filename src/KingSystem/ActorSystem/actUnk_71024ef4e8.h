#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {
class Constraint;
}

namespace ksys::act {

// Placeholder name (vtable 0x71024ef4e8, only a trivial virtual dtor; methods in 0x7100eb2394-0x7100eb5900;
// created with `new(0x2b8)` by 0x7100eb16a0 (CSV ActorPhysics::x_8, called with the actor's phys::InstanceSet
// and Model by Player::prepareInit_). Stored in Player::_1870 (the object behind Player's slots
// m41 / m42 / m47 and getAttachedTargetActor). Holds the body's transform at +0xe0 (a second copy at +0x188).
// TODO: incomplete.
class Unk_71024ef4e8 {
public:
    // Placeholder: the object at `_b0` (a BaseProcLink of the attached actor lives at +0x158, a Constraint* at +8).
    struct AttachInfo {
        // 0x7100eb0d30 (out of line; defined in its own file so that the caller does not inline it).
        void sub_7100EB0D30();

        u8 _0[8];
        phys::Constraint* mConstraint;
        u8 _10[0x158 - 0x10];
        BaseProcLink mTargetLink;
    };

    virtual ~Unk_71024ef4e8() = default;

    // 0x7100eb2448: `if (mAttachInfo) mAttachInfo->sub_7100EB0D30()` (calls Constraint::sub_7100F6A074 on the attach constraint).
    void sub_7100EB2448();
    // 0x7100eb57f0: stores `mtx` into _e0 / _188 (resets the scale at _1b8 to 1) and updates the flags at _110.
    void sub_7100EB57F0(const sead::Matrix34f& mtx);

    /* 0x008 */ u8 _8[0xb0 - 0x8];
    /* 0x0b0 */ AttachInfo* mAttachInfo;
    u8 _b8[0xe0 - 0xb8];
    /* 0x0e0 */ sead::Matrix34f mMtx;
        /* 0x110 */ u32 _110;  // flags
    u8 _114[0x188 - 0x114];
    /* 0x188 */ sead::Matrix34f _188;
    /* 0x1b8 */ f32 _1b8;
    /* 0x1bc */ f32 _1bc;
    u8 _1c0[0x2b8 - 0x1c0];
};
KSYS_CHECK_SIZE_NX150(Unk_71024ef4e8, 0x2b8);

}  // namespace ksys::act
