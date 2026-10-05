#include "Game/AI/AI/aiAnimalEscapeAI.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

AnimalEscapeAI::AnimalEscapeAI(const InitArg& arg) : AnimalRoamBase(arg) {}

AnimalEscapeAI::~AnimalEscapeAI() = default;

bool AnimalEscapeAI::init_(sead::Heap* heap) {
    return AnimalRoamBase::init_(heap);
}

void AnimalEscapeAI::enter_(ksys::act::ai::InlineParamPack* params) {
    AnimalRoamBase::enter_(params);
}

// NON_MATCHING: Finite radius comparison uses a different equivalent branch after the NaN check.
void AnimalEscapeAI::leave_() {
    AnimalRoamBase::leave_();
    if (auto* nav = mActor->m45()) {
        {
            auto lock = sead::makeScopedLock(nav->_1e0);
            nav->_2b0 = 1.0f;
            nav->_220 |= 0x20;
        }
        if (!_120.isNan()) {
            auto lock = sead::makeScopedLock(nav->_1e0);
            nav->_284 = _120;
        }
        const f32 radius_scale = _12c;
        if (!sead::Mathf::isNan(radius_scale) &&
            sead::Mathf::abs(radius_scale) <= sead::Mathf::maxNumber() &&
            nav->_2ac != radius_scale) {
            auto lock = sead::makeScopedLock(nav->_1e0);
            nav->_2ac = radius_scale;
            nav->_220 |= 0x10;
        }
    }
}

void AnimalEscapeAI::loadParams_() {
    AnimalRoamBase::loadParams_();
    getStaticParam(&mNumTimesAllowStuck_s, "NumTimesAllowStuck");
    getStaticParam(&mContinueDistance_s, "ContinueDistance");
    getStaticParam(&mShouldEscapeDistance_s, "ShouldEscapeDistance");
    getStaticParam(&mShouldEscapeDistanceRand_s, "ShouldEscapeDistanceRand");
    getStaticParam(&mPenaltyScale_s, "PenaltyScale");
    getStaticParam(&mNavMeshRadiusScale_s, "NavMeshRadiusScale");
    getStaticParam(&mFramesStuckOnTerrainAction_s, "FramesStuckOnTerrainAction");
    getStaticParam(&mIsSendGoalPos_s, "IsSendGoalPos");
    getStaticParam(&mIsUseBeforeAction_s, "IsUseBeforeAction");
    getStaticParam(&mIsDynamicallyOffsetNavChar_s, "IsDynamicallyOffsetNavChar");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getAITreeVariable(&mIsUseTerritory_a, "IsUseTerritory");
}

bool AnimalEscapeAI::m37() {
    return isCurrentChild("逃走前");
}

}  // namespace uking::ai
