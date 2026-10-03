#include "Game/AI/Action/actionLastBossFlyWait.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

LastBossFlyWait::LastBossFlyWait(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LastBossFlyWait::~LastBossFlyWait() = default;

bool LastBossFlyWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LastBossFlyWait::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mIsResetEndTime_d || _84 <= 0.0f) {
        _7c = *mTime_s;
        _78 = _7c;
        _80 = -1.0f;
        const f32 range = *mEndTimeRandRange_s;
        const f32 rand = sead::GlobalRandom::instance()->getF32();
        const f32 end_time = *mEndTime_s + range * rand;
        _8c = -1.0f;
        _88 = end_time;
        _84 = end_time;
    }
    _90 = mActor->getMtx().m[1][3] + *mBaseYOffset_s;
    _94 = 0.5f;
    _98 = 0;
    playAS(mWaitAS_s.cstr(), true, 0, 0, -1.0f);
    if (*mEndTime_s <= 0.0f)
        setFinished();
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
