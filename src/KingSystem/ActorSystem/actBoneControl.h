#pragma once

#include <basis/seadTypes.h>
#include <gsys/gsysModelAccessKey.h>
#include <math/seadVector.h>
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}

namespace ksys {

namespace res {
class BoneControl;
}

namespace act {

class Actor;

// Unnamed classes of the actor bone control code (0x7100d82b74 - 0x7100d8bxxx). The class names are
// placeholders (Unk_<ctor address>); Actor::mBoneControl -> BoneControl::_0 -> Unk_7100d8557c, which
// holds two controllers (Unk_7100d860d8 at 0x10, initialised from res::BoneControl's spine data, and
// Unk_7100d83054 at 0xe8).

// Size 0xd8. ctor 0x7100d860d8.
class Unk_7100d860d8 {
public:
    explicit Unk_7100d860d8(Actor* actor);

    void sub_7100D88CF4(sead::Vector3f* out) const;
    void sub_7100D892C4(sead::Vector3f* out) const;
    void sub_7100D89348(const f32& a1, const f32& a2);
    f32 sub_7100D8A6DC() const;
    f32 sub_7100D8A76C() const;
    void sub_7100D8A830(const f32& value, bool a2);
    void sub_7100D8A904(const f32& value, bool a2);

    /* 0x00 */ Actor* mActor;
    /* 0x08 */ sead::Vector3f _8;
    /* 0x14 */ u32 _14;
    // array of 0x180-byte nodes (element type unknown)
    /* 0x18 */ s32 _18;
    /* 0x20 */ void* _20;
    /* 0x28 */ s32 _28;
    /* 0x30 */ gsys::BoneAccessKeyEx _30;
    /* 0x68 */ sead::Vector3f _68;
    /* 0x74 */ sead::Vector3f _74;
    /* 0x80 */ sead::Vector3f _80;
    /* 0x8c */ u16 _8c;
    /* 0x90 */ f32 _90[16];
    /* 0xd0 */ f32 _d0;
    /* 0xd4 */ u32 _d4;
};
KSYS_CHECK_SIZE_NX150(Unk_7100d860d8, 0xd8);

// Size 0x48. ctor 0x7100d83054.
class Unk_7100d83054 {
public:
    explicit Unk_7100d83054(Actor* actor);

    /* 0x00 */ Actor* mActor;
    /* 0x08 */ sead::Vector3f _8;
    /* 0x14 */ f32 _14;
    /* 0x18 */ f32 _18;
    /* 0x1c */ f32 _1c;
    /* 0x20 */ f32 _20;
    /* 0x24 */ u32 _24;
    /* 0x28 */ f32 _28;
    /* 0x2c */ u32 _2c;  // not initialised by the ctor
    /* 0x30 */ s32 _30;
    /* 0x38 */ void* _38;
    /* 0x40 */ s32 _40;
};
KSYS_CHECK_SIZE_NX150(Unk_7100d83054, 0x48);

// Size 0x130 (BoneControl::init: new(0x130)). ctor 0x7100d8557c.
class Unk_7100d8557c {
public:
    explicit Unk_7100d8557c(Actor* actor);

    /// Sets _10._8 and _e8._8.
    void sub_7100D8571C(const sead::Vector3f& pos);
    void sub_7100D85750();
    void sub_7100D85774();
    void sub_7100D85794();
    void sub_7100D857B0();

    /* 0x000 */ Actor* mActor;
    /* 0x008 */ f32 _8 = 1.0f;
    /* 0x00c */ f32 _c = 1.0f;
    /* 0x010 */ Unk_7100d860d8 _10;
    /* 0x0e8 */ Unk_7100d83054 _e8;
};
KSYS_CHECK_SIZE_NX150(Unk_7100d8557c, 0x130);

// Actor::mBoneControl (CSV: ActorBoneControl). Size 8 (Actor::init: new(8)).
class BoneControl {
public:
    BoneControl();

    bool init(Actor* actor, res::BoneControl* res, sead::Heap* heap);
    // 0x7100d82fc4: _0->sub_7100D857B0() if _0 is set (declaration only).
    void sub_7100D82FC4();

    /* 0x0 */ Unk_7100d8557c* _0 = nullptr;
};
KSYS_CHECK_SIZE_NX150(BoneControl, 0x8);

bool sub_7100D83014(sead::Vector3f* out, const BoneControl* bone_control);

}  // namespace act

}  // namespace ksys
