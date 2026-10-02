#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/System/Timer.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class Actor;

// Placeholder name (no vtable; inline ctor; methods 0x7100d3bc4c / 0x7100d3bce4, after BoneHandleBase):
// a ksys::Timer advanced by the delta frame plus the actor's LodState::_40. Embedded in
// ForkLodTimer (+0x38), ForkDrownTimer, BalloonBase, EnemyBaseFindPlayer, LynelRecognizeTarget, ...
// The owner's ctor stores the actor and zeroes the timer.
class Unk_7100d3bc4c {
public:
    explicit Unk_7100d3bc4c(Actor* actor) : mActor(actor) {}
    // LimitedTimeredActorCreator starts the timer at 1 (value and previous value 1, rate 0).
    Unk_7100d3bc4c(Actor* actor, f32 value) : mActor(actor), mTimer(value, value, 0.0f) {}

    // value += (delta frame + LOD delta) * rate.
    void sub_7100D3BC4C(f32 rate);
    // Like ksys::Timer::update(): previous_value = value, then value += (delta + LOD delta) * rate.
    void sub_7100D3BCE4();

    /* 0x00 */ Actor* mActor;
    /* 0x08 */ Timer mTimer;
};
KSYS_CHECK_SIZE_NX150(Unk_7100d3bc4c, 0x18);

}  // namespace ksys::act
