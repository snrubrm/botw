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
