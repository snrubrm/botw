#include "Game/AI/AI/aiNavMeshTurnAwayFromHitPos.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "Game/AI/aiUnk_7100742478.h"
#include <prim/seadScopedLock.h>

namespace uking::ai {

NavMeshTurnAwayFromHitPos::NavMeshTurnAwayFromHitPos(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NavMeshTurnAwayFromHitPos::~NavMeshTurnAwayFromHitPos() = default;

bool NavMeshTurnAwayFromHitPos::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NavMeshTurnAwayFromHitPos::enter_(ksys::act::ai::InlineParamPack*) {
    auto* nav = mActor->m45();
    if (!nav) {
        setFailed();
        return;
    }
    // Native validated setter: also used by matching EnemyHorseRide::leave_.
    if (!sead::Vector3f::zero.isNan()) {
        auto lock = sead::makeScopedLock(nav->_1e0);
        nav->_284 = sead::Vector3f::zero;
    }
    sub_71004B56B4();
    ksys::act::ai::InlineParamPack params;
    params.addVec3(_60, "TargetPos", -1);
    changeChild("回転", &params);
}

// NON_MATCHING: vector normalization, rotation and probe argument scheduling differ.
// 0x71004b56b4
void NavMeshTurnAwayFromHitPos::sub_71004B56B4() {
    const sead::Vector3f position = mActor->getMtx().getTranslation();
    sead::Vector3f away(position.x - mHitPos_d->x, 0.0f, position.z - mHitPos_d->z);
    away.normalize();
    sead::Vector3f toward(mTargetPos_d->x - position.x, 0.0f, mTargetPos_d->z - position.z);
    toward.normalize();
    auto* nav = mActor->m45();
    if (!nav) {
        setFailed();
        return;
    }
    sead::Vector3f direction = away * 0.25f + toward * 0.75f;
    direction.normalize();
    if (direction.isNan())
        direction = -nav->_248;
    const f32 turn_sign = toward.cross(direction).dot(sead::Vector3f::ey) > 0.0f ? 1.0f : -1.0f;
    const f32 angle = sead::Mathf::pi() / *mNumLOSCheckMax_s * turn_sign;
    sead::Matrix33f rotation;
    rotation.makeR({0.0f, angle, 0.0f});
    for (s32 i = 0; i < *mNumLOSCheckMax_s; ++i) {
        sead::Vector3f hit;
        if (sub_7100742664(&hit, nav, &direction, *mLOSCheckLength_s, 10.0f)) {
            _60 = position + direction * *mLOSCheckLength_s;
            return;
        }
        direction = rotation * direction;
    }
    _60 = direction;
}

void NavMeshTurnAwayFromHitPos::calc_() {
    if (isFinished() || isFailed())
        return;

    auto* child = getCurrentChild();
    if (child) {
        if (!child->isFinished() && !child->isFailed())
            return;

        if (!child->isFailed()) {
            if (isCurrentChild("回転") && *mMoveToSafePosAfterTurn_s) {
                ksys::act::ai::InlineParamPack params;
                params.addVec3(_60, "TargetPos", -1);
                changeChild("移動", &params);
            } else {
                setFinished();
            }
            return;
        }
    }
    setFailed();
}

void NavMeshTurnAwayFromHitPos::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NavMeshTurnAwayFromHitPos::loadParams_() {
    getStaticParam(&mNumLOSCheckMax_s, "NumLOSCheckMax");
    getStaticParam(&mLOSCheckLength_s, "LOSCheckLength");
    getStaticParam(&mMoveToSafePosAfterTurn_s, "MoveToSafePosAfterTurn");
    getDynamicParam(&mHitPos_d, "HitPos");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
