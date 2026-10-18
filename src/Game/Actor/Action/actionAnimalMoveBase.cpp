#include "Game/Actor/Action/actionAnimalMoveBase.h"
#include "KingSystem/System/VFR.h"
#include <random/seadGlobalRandom.h>
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

AnimalMoveBase::AnimalMoveBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AnimalMoveBase::~AnimalMoveBase() = default;

bool AnimalMoveBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AnimalMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    auto* rideable = mActor->m132();
    if (!rideable) {
        setFailed();
        return;
    }
    const s32 max = *mMaxUseGear_s;
    s32 gear = *mMinUseGear_s;
    if (max >= gear) {
        auto* random = sead::GlobalRandom::instance();
        gear += random->getU32((max + 1) - gear);
    }
    _68 = gear;
    if (*mCanUseHorseGearInput_s) {
        const act::Rideable::Gear input_gear(rideable->_134);
        if (int(input_gear) > 0)
            gear = rideable->_134;
    }
    rideable->sub_7100E63224(u32(*mUseGearType_s), u32(gear));
    rideable->_18.sub_7100E770C4(false);
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

// NON_MATCHING: original enum identities of the three integer movement arguments are unknown.
bool AnimalMoveBase::m35(act::RideableBase* rideable, s32 gear_type, s32 gear,
                         s32 min_gear_at_auto_down, const sead::Vector3f& direction) {
    return rideable->sub_7100E63560(gear_type, gear, min_gear_at_auto_down, direction, 0);
}

}  // namespace uking::action
