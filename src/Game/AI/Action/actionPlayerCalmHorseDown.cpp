#include "Game/AI/Action/actionPlayerCalmHorseDown.h"
#include "Game/Actor/actHorseObject.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

PlayerCalmHorseDown::PlayerCalmHorseDown(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PlayerCalmHorseDown::~PlayerCalmHorseDown() = default;

bool PlayerCalmHorseDown::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PlayerCalmHorseDown::enter_(ksys::act::ai::InlineParamPack* params) {
    _38 = 0.0f;
    _3c = 0;
    mFlags.reset(Flag::Changeable);
}

void PlayerCalmHorseDown::leave_() {
    if (auto* ride_actor = act::getRideActor(mActor)) {
        if (auto* rideable = ride_actor->getHorseOptionsMaybe()) {
            if (auto* reins = rideable->m40()) {
                reins->_850.acquire(nullptr, false);
                reins->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
            }
        }
    }
}

void PlayerCalmHorseDown::loadParams_() {
    getStaticParam(&mPlayCalmDownAnimFrames_s, "PlayCalmDownAnimFrames");
    getStaticParam(&mEnergyDecreasePerSec_s, "EnergyDecreasePerSec");
    getDynamicParam(&mHasToPlayRidingOnAS_d, "HasToPlayRidingOnAS");
}

void PlayerCalmHorseDown::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
