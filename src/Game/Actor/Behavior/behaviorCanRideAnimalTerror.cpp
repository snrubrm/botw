#include "Game/Actor/Behavior/behaviorCanRideAnimalTerror.h"

#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"
#include <math/seadMathCalcCommon.h>

namespace uking::behavior {

CanRideAnimalTerror::CanRideAnimalTerror(const InitArg& arg) : TerrorBehavior(arg) {}

CanRideAnimalTerror::~CanRideAnimalTerror() = default;

bool CanRideAnimalTerror::init_(sead::Heap* heap) {
    return TerrorBehavior::init_(heap);
}

void CanRideAnimalTerror::enter() {
    TerrorBehavior::enter();
    _160 = ksys::Timer(-1.0f, -1.0f);
}

void CanRideAnimalTerror::leave() {
    TerrorBehavior::leave();
}

void CanRideAnimalTerror::loadParams() {
    TerrorBehavior::loadParams();
    getStaticParam(&mLevelForRiddenPlayer_s, "LevelForRiddenPlayer");
}

void CanRideAnimalTerror::calc() {
    TerrorBehavior::calc();
    sub_710061B944();
}

// NON_MATCHING: the level-dependent request setup is shared rather than duplicated across the two branches.
void CanRideAnimalTerror::sub_710061B944() {
    auto* rideable = mActor->getHorseOptionsMaybe();
    if (!rideable)
        return;
    bool active;
    if (u8(rideable->act::Unk_7100e8b2b8::_8.load()) == 1 &&
        !(rideable->act::Unk_7100e8b2b8::_8.load() & 0x400)) {
        _160.reset(150.0f);
        active = true;
    } else if (!(_160.value <= sead::Mathf::epsilon())) {
        _160.update();
        if (mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_8000000))
            _160.reset(30.0f);
        active = true;
    } else {
        active = false;
    }
    if (active != _16c) {
        const f32 level = static_cast<f32>(active ? *mLevelForRiddenPlayer_s : *mLevel_s);
        const u32 flags = sub_7100E93098();
        _a0._10._10.makeAllZero();
        _a0._10._18.m15();
        _a0.x(2, flags, level);
        _a0.setRadius(*mRadius_s);
    }
    _16c = active;
}

}  // namespace uking::behavior
