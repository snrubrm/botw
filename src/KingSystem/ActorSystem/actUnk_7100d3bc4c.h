#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/System/Timer.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class Actor;

// Placeholder name (no vtable; inline ctor; method 0x7100d3bc4c, after BoneHandleBase): a float
// counter advanced by the delta frame plus the actor's LodState::_40, times a rate passed by the
// caller. Size 0x10: LynelRecognizeTarget embeds two at +0x100 / +0x110; EnemyBaseFindPlayer (+0x108,
// own fields from +0x118), MimicEnemyFindPlayer (+0x108), FlyingEnemySideKeepMove (+0x98),
// ForkDrownTimer (+0x30). The owner's ctor stores the actor and zeroes the value.
class Unk_7100d3bc4c {
public:
    explicit Unk_7100d3bc4c(Actor* actor) : mActor(actor) {}

    // value += (delta frame + LOD delta) * rate.
    void sub_7100D3BC4C(f32 rate);

    /* 0x00 */ Actor* mActor;
    /* 0x08 */ f32 mValue = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_7100d3bc4c, 0x10);

// Placeholder name (no vtable; inline ctor; method 0x7100d3bce4, right after 0x7100d3bc4c): a
// ksys::Timer advanced by the delta frame plus the actor's LodState::_40. Size 0x18 (SandwormBattle
// embeds two at +0x58 / +0x70, RemainsWaterBattleRoot three at +0x68 / +0x80 / +0x98). Embedded in
// ForkLodTimer (+0x38), BalloonBase, GolemReaction, LimitedTimeredActorCreator, ...
// The owner's ctor stores the actor and zeroes the timer.
class Unk_7100d3bce4 {
public:
    explicit Unk_7100d3bce4(Actor* actor) : mActor(actor) {}
    // LimitedTimeredActorCreator starts the timer at 1 (value and previous value 1, rate 0).
    Unk_7100d3bce4(Actor* actor, f32 value) : mActor(actor), mTimer(value, value, 0.0f) {}

    // Like ksys::Timer::update(): previous_value = value, then value += (delta + LOD delta) * rate.
    void sub_7100D3BCE4();

    /* 0x00 */ Actor* mActor;
    /* 0x08 */ Timer mTimer;
};
KSYS_CHECK_SIZE_NX150(Unk_7100d3bce4, 0x18);

}  // namespace ksys::act
