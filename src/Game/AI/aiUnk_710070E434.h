#pragma once

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actBoneHandle.h"

namespace ksys::act {
class Actor;
}

// Placeholder name (first method 0x710070e434; no name known): the "leg turn" state shared by
// AnimalASPlayWithLegTurn (+0x80), AnimalLegTurnAutoSpeed (+0x78), ForkASHoldLegTurn,
// LynelAttackASPlay (+0xa8) and the Giant*WithLegTurn actions. It lets a bone of the actor's model
// (the leg) follow a target direction: `_70` is the BoneHandle applied to the model every frame.
// Its constructor is inlined into the owners.
struct Unk_710070e434 {
    explicit Unk_710070e434(ksys::act::Actor* actor) : mActor(actor) {}

    // 0x710070e434: sets the bone name (empty = no bone); registers `_70` with the actor.
    void sub_710070E434(const sead::SafeString& name);
    // 0x710070e4c0: removes `_70` from the actor.
    void sub_710070E4C0();
    // 0x710070e4ec (declared only): reads the bone's current pose into `_10` / `_1c` / `_40`.
    void sub_710070E4EC(const sead::SafeString& name);
    // 0x710070e714: `_10` = actor matrix * `_40`.
    void sub_710070E714();
    // 0x710070e7a8 (declared only): per-frame update towards `target`.
    void sub_710070E7A8(const sead::Vector3f* target, f32 rot_ratio, f32 rot_speed, f32 rot_acc_ratio);

    ksys::act::Actor* mActor;
    f32 _8 = 0;
    bool _c = false;
    sead::Vector3f _10;
    sead::Matrix33f _1c;
    sead::Vector3f _40;
    sead::Matrix33f _4c;
    ksys::act::BoneHandle _70;
};
static_assert(sizeof(Unk_710070e434) == 0x118);
