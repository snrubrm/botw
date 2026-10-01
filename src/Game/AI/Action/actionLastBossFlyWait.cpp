#include "Game/AI/Action/actionLastBossFlyWait.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

LastBossFlyWait::LastBossFlyWait(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LastBossFlyWait::~LastBossFlyWait() = default;

bool LastBossFlyWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LastBossFlyWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void LastBossFlyWait::leave_() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    }
}

void LastBossFlyWait::loadParams_() {
    getStaticParam(&mDamageCounter_s, "DamageCounter");
    getStaticParam(&mAmplitude_s, "Amplitude");
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mMoveRate_s, "MoveRate");
    getStaticParam(&mEndTime_s, "EndTime");
    getStaticParam(&mEndTimeRandRange_s, "EndTimeRandRange");
    getStaticParam(&mBaseYOffset_s, "BaseYOffset");
    getStaticParam(&mIsChemicalOff_s, "IsChemicalOff");
    getStaticParam(&mWaitAS_s, "WaitAS");
    getDynamicParam(&mIsResetEndTime_d, "IsResetEndTime");
}

void LastBossFlyWait::calc_() {
    ksys::act::ai::Action::calc_();
}

bool LastBossFlyWait::isChangeable() const {
    return true;
}

}  // namespace uking::action
