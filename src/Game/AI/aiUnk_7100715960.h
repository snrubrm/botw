#pragma once

#include <basis/seadTypes.h>
#include <cfloat>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actBoneHandle.h"

namespace ksys::act {
class Actor;
}

// Placeholder name (first method 0x7100715960 = the out-of-line constructor; no name known): the "leg turn" state of
// the Giant*WithLegTurn actions (embedded at +0x180 of GiantOneHandActionWithLegTurn). Like Unk_710070e434 it lets a
// bone of the actor's model follow a target; `_40` is the BoneHandle applied to the model every frame, `_18` / `_24`
// the rotation offset limits (the actions copy `RotOffsetMin` / `RotOffsetMax` / `BaseTargetPos` into it) and
// `_e8` - `_f4` the trace angle / distance limits.
struct Unk_7100715960 {
    explicit Unk_7100715960(ksys::act::Actor* actor);
    ~Unk_7100715960();

    // 0x7100715a20: sets the bone name, resets the bone matrix and adds `_40` to the actor (`target` is unused).
    void sub_7100715A20(sead::Vector3f* target, const sead::SafeString& bone_name);
    // 0x7100715b3c: removes `_40` from the actor.
    void sub_7100715B3C();
    // 0x7100715b4c (declared only): per-frame update towards `target`.
    void sub_7100715B4C(sead::Vector3f* target);
    // 0x7100715c6c / 0x7100715e94 (declared only): `out` = the direction to the target in the bone's frame /
    // the rotation (euler angles) that turns the bone towards it (first-pass guesses).
    void sub_7100715C6C(sead::Vector3f* out, sead::Vector3f* target);
    void sub_7100715E94(sead::Vector3f* out, const sead::Vector3f* dir);
    // 0x7100716264 (declared only): per-frame update without a target (argument: the time / speed constant).
    void sub_7100716264(f32 value);

    /* 0x00 */ ksys::act::Actor* mActor;
    /* 0x08 */ sead::SafeString _8;
    /* 0x18 */ sead::Vector3f _18{-FLT_MAX, -FLT_MAX, -FLT_MAX};
    /* 0x24 */ sead::Vector3f _24{FLT_MAX, FLT_MAX, FLT_MAX};
    /* 0x30 */ sead::Vector3f _30;
    /* 0x40 */ ksys::act::BoneHandle _40;
    /* 0xe8 */ f32 _e8 = -3.14159265f;
    /* 0xec */ f32 _ec = 3.14159265f;
    /* 0xf0 */ f32 _f0 = 0.0f;
    /* 0xf4 */ f32 _f4 = __builtin_inff();
    /* 0xf8 */ bool _f8 = false;
};
static_assert(sizeof(Unk_7100715960) == 0x100);
