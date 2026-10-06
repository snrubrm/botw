#include "Game/AI/Action/actionAnimalMoveStraightTimed.h"
#include <random/seadGlobalRandom.h>
#include "Game/Actor/actRideable.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

AnimalMoveStraightTimed::AnimalMoveStraightTimed(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AnimalMoveStraightTimed::~AnimalMoveStraightTimed() = default;

bool AnimalMoveStraightTimed::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the original loads the two range params before the GlobalRandom instance pointer.
void AnimalMoveStraightTimed::enter_(ksys::act::ai::InlineParamPack* params) {
    _68.reset(*mFramesUntilFinish_s);
    if (auto* rideable = mActor->m132()) {
        const s32 gear = sead::GlobalRandom::instance()->getS32Range(*mMinUseGear_s, *mMaxUseGear_s);
        rideable->sub_7100E63224(u32(*mUseGearType_s), u32(gear));
    } else {
        setFailed();
    }
}

void AnimalMoveStraightTimed::leave_() {
    if (auto* navmesh = mActor->m45())
        navmesh->sub_7100F76314();
}

void AnimalMoveStraightTimed::loadParams_() {
    getStaticParam(&mFramesUntilFinish_s, "FramesUntilFinish");
    getStaticParam(&mMinUseGear_s, "MinUseGear");
    getStaticParam(&mMaxUseGear_s, "MaxUseGear");
    getStaticParam(&mUseGearType_s, "UseGearType");
    getStaticParam(&mMinGearAtAutoGearDown_s, "MinGearAtAutoGearDown");
    getStaticParam(&mLOSCheckTimeAhead_s, "LOSCheckTimeAhead");
    getStaticParam(&mIsFinishOnLOSCheckFail_s, "IsFinishOnLOSCheckFail");
    getStaticParam(&mUseDesiredMoveDir_s, "UseDesiredMoveDir");
    getStaticParam(&mIsAutoGearDownEnabled_s, "IsAutoGearDownEnabled");
}

void AnimalMoveStraightTimed::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
