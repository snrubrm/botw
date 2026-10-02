#include "Game/AI/Action/actionAnimalMoveBase.h"
#include "KingSystem/System/VFR.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

AnimalMoveBase::AnimalMoveBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AnimalMoveBase::~AnimalMoveBase() = default;

bool AnimalMoveBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AnimalMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AnimalMoveBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void AnimalMoveBase::loadParams_() {
    getStaticParam(&mMinUseGear_s, "MinUseGear");
    getStaticParam(&mMaxUseGear_s, "MaxUseGear");
    getStaticParam(&mUseGearType_s, "UseGearType");
    getStaticParam(&mMinGearAtAutoGearDown_s, "MinGearAtAutoGearDown");
    getStaticParam(&mGoalDistanceTolerance_s, "GoalDistanceTolerance");
    getStaticParam(&mCanUseHorseGearInput_s, "CanUseHorseGearInput");
    getStaticParam(&mIsAutoGearDownEnabled_s, "IsAutoGearDownEnabled");
    getStaticParam(&mHasToDecelerateNearGoal_s, "HasToDecelerateNearGoal");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void AnimalMoveBase::calc_() {
    ksys::act::ai::Action::calc_();
}

sead::Vector3f* AnimalMoveBase::m32() {
    return mTargetPos_d;
}

bool AnimalMoveBase::m33(float x) {
    return false;
}

bool AnimalMoveBase::m34(const sead::Vector3f& pos, float x) {
    const f32 dist = ksys::VFR::instance()->getDeltaFrame() * x * 2.0f;
    if (dist > 0.0f && sub_710072FEC4(mActor, pos, dist, nullptr, true, nullptr))
        return false;
    return true;
}

}  // namespace uking::action
