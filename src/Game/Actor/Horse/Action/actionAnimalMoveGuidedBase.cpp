#include "Game/Actor/Horse/Action/actionAnimalMoveGuidedBase.h"
#include <random/seadGlobalRandom.h>
#include "Game/Actor/actRideable.h"
#include "Game/Actor/actHorseStrings.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

AnimalMoveGuidedBase::AnimalMoveGuidedBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

bool AnimalMoveGuidedBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AnimalMoveGuidedBase::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    auto* rideable = mActor->m132();
    if (!rideable) {
        setFailed();
        return;
    }
    const s32 max_gear = *mMaxUseGear_s;
    s32 gear = *mMinUseGear_s;
    if (max_gear >= gear)
        gear += sead::GlobalRandom::instance()->getU32((max_gear + 1) - gear);
    _70 = gear;
    rideable->sub_7100E534A0(act::sUnk_7102603220.cstr(), act::sUnk_7102603180.cstr(), nullptr);
    _74 = false;
}

void AnimalMoveGuidedBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void AnimalMoveGuidedBase::loadParams_() {
    getStaticParam(&mMinUseGear_s, "MinUseGear");
    getStaticParam(&mMaxUseGear_s, "MaxUseGear");
    getStaticParam(&mUseGearType_s, "UseGearType");
    getStaticParam(&mAutoStopAndTurnMode_s, "AutoStopAndTurnMode");
    getStaticParam(&mMinGearAtAutoGearDown_s, "MinGearAtAutoGearDown");
    getStaticParam(&mGoalDistanceTolerance_s, "GoalDistanceTolerance");
    getStaticParam(&mCanUseHorseGearInput_s, "CanUseHorseGearInput");
    getStaticParam(&mIsAutoGearDownEnabled_s, "IsAutoGearDownEnabled");
    getStaticParam(&mHasToDecelerateNearGoal_s, "HasToDecelerateNearGoal");
    getStaticParam(&mWaitUntilPathSucceeded_s, "WaitUntilPathSucceeded");
}

void AnimalMoveGuidedBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
