#include "Game/AI/Action/actionImmediateStopOwnedHorse.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"

// The original source owner is unknown; keep the declaration in the global scope.
ksys::act::Actor* sub_710072BB4C();

namespace uking::action {

ImmediateStopOwnedHorse::ImmediateStopOwnedHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ImmediateStopOwnedHorse::~ImmediateStopOwnedHorse() = default;

bool ImmediateStopOwnedHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ImmediateStopOwnedHorse::loadParams_() {
    getDynamicParam(&mResetChargeNum_d, "ResetChargeNum");
}

// NON_MATCHING: flag-mask register allocation and scheduling differ.
bool ImmediateStopOwnedHorse::oneShot_() {
    if (auto* player = sub_710072BB4C()) {
        if (auto* horse = act::getRideActor(player)) {
            if (auto* rideable = horse->getHorseOptionsMaybe()) {
                rideable->Unk_7100e8b2b8::_10 |=
                    1u << act::Unk_7100e8b2b8::Flag10(act::Unk_7100e8b2b8::Flag10::_1);
                if (*mResetChargeNum_d)
                    rideable->RideableBase::_8 |= 0x1000;
            }
        }
    }
    return true;
}

}  // namespace uking::action
