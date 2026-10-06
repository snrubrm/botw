#include "Game/AI/AI/aiAnimalEscapeAI.h"
#include <limits>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
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

// NON_MATCHING: the original keeps the escape distance `_148` in a callee-saved register from before the length
// computation (frame 0x80 instead of 0x70).
void AnimalEscapeAI::changeToEscape() {
    sead::Vector3f target;
    if (*mIsSendGoalPos_s) {
        if (m35()) {
            auto* nav = mActor->m45();
            auto lock = sead::makeScopedLock(nav->_1e0);
            target = nav->_194;
        } else {
            const sead::Vector3f position = mActor->getMtx().getTranslation();
            sead::Vector3f direction = position - *mTargetPos_d;
            const f32 distance = _148;
            const f32 length = direction.length();
            if (length > 0.0f)
                direction *= distance / length;
            target = position + direction;
        }
    } else {
        target = {std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN(),
                  std::numeric_limits<f32>::quiet_NaN()};
    }
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target, "TargetPos", -1);
    m38(&pack);
    changeChild("逃走", &pack);
}

// NON_MATCHING: instruction scheduling of the hit position (the original interleaves the loads of the forward axis
// and the translation differently).
void AnimalEscapeAI::changeToStuckOnTerrain() {
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f target;
    sead::Vector3f forward;
    mActor->getMtx().getBase(forward, 2);
    const sead::BoundBox3f& aabb = mActor->getAabb();
    sead::Vector3f hit_position;
    hit_position.setScaleAdd((aabb.getMax().z - aabb.getMin().z) * 0.5f, forward, mActor->getMtx().getTranslation());
    {
        auto* nav = mActor->m45();
        auto lock = sead::makeScopedLock(nav->_1e0);
        target = nav->_194;
    }
    pack.addVec3(target, "TargetPos", -1);
    pack.addVec3(hit_position, "HitPos", -1);
    changeChild("地形嵌り", &pack);
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
