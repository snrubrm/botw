#include "Game/AI/Behavior/behaviorHorseSlipBehavior.h"
#include "Game/Actor/actHorseStrings.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::behavior {

HorseSlipBehavior::HorseSlipBehavior(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

HorseSlipBehavior::~HorseSlipBehavior() = default;

bool HorseSlipBehavior::m6(sead::Heap* heap) {
    return true;
}

// NON_MATCHING: the original tail-calls sub_7100F5F07C without a frame record (ours sets up x29 / x30 and calls)
void HorseSlipBehavior::sub_7100E61830(ksys::phys::CharacterController* controller,
                                       act::Rideable* rideable) {
    const act::Rideable::Gear gear(*(rideable->_18._b == 0 ? &rideable->_18._9 : &rideable->_18._b));
    switch (gear) {
    case act::Rideable::Gear::_0:
        controller->sub_7100F5F07C(*mSlipAngleDeg_s);
        break;
    case act::Rideable::Gear::_1:
        controller->sub_7100F5F07C(*mSlipAngleDegGear1_s);
        break;
    case act::Rideable::Gear::_2:
        controller->sub_7100F5F07C(*mSlipAngleDegGear2_s);
        break;
    case act::Rideable::Gear::_3:
        controller->sub_7100F5F07C(*mSlipAngleDegGear3_s);
        break;
    case act::Rideable::Gear::_4:
        controller->sub_7100F5F07C(*mSlipAngleDegGearTop_s);
        break;
    default:
        break;
    }
}

void HorseSlipBehavior::m9() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5E754(false);
    if (mActor->getASList()->x_1(0, 0) == act::sUnk_7102603270) {
        if (auto* rideable = mActor->getHorseOptionsMaybe())
            rideable->_18.sub_7100E76E74(act::sUnk_7102603280, false);
    }
}

void HorseSlipBehavior::loadParams() {
    getStaticParam(&mSlipAngleDeg_s, "SlipAngleDeg");
    getStaticParam(&mSlipAngleDegGear1_s, "SlipAngleDegGear1");
    getStaticParam(&mSlipAngleDegGear2_s, "SlipAngleDegGear2");
    getStaticParam(&mSlipAngleDegGear3_s, "SlipAngleDegGear3");
    getStaticParam(&mSlipAngleDegGearTop_s, "SlipAngleDegGearTop");
    getStaticParam(&mSlipEndAngleDeg_s, "SlipEndAngleDeg");
    getStaticParam(&mMaxSlipAngleDeg_s, "MaxSlipAngleDeg");
    getStaticParam(&mSlipFramesThreshold_s, "SlipFramesThreshold");
    getStaticParam(&mSlipValueThreshold_s, "SlipValueThreshold");
    getStaticParam(&mSlipRecoveryFactor_s, "SlipRecoveryFactor");
    getStaticParam(&mSlipVelocityMax_s, "SlipVelocityMax");
    getStaticParam(&mSlipVelocityAddScale_s, "SlipVelocityAddScale");
    getStaticParam(&mSlipSpeedAttn_s, "SlipSpeedAttn");
    getStaticParam(&mLimitGear1FrameThreshold_s, "LimitGear1FrameThreshold");
}

}  // namespace uking::behavior
