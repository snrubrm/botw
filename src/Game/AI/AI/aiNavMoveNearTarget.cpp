#include "Game/AI/AI/aiNavMoveNearTarget.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71007320F0.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

NavMoveNearTarget::NavMoveNearTarget(const InitArg& arg) : NavMoveTarget(arg) {}

NavMoveNearTarget::~NavMoveNearTarget() = default;

bool NavMoveNearTarget::init_(sead::Heap* heap) {
    return NavMoveTarget::init_(heap);
}

void NavMoveNearTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    _390 = *mTargetPos_d;
    m35(nullptr);
    NavMoveTarget::enter_(params);
}

void NavMoveNearTarget::leave_() {
    NavMoveTarget::leave_();
}

void NavMoveNearTarget::loadParams_() {
    NavMoveTarget::loadParams_();
    getStaticParam(&mTargetVMax_s, "TargetVMax");
    getStaticParam(&mTargetVMin_s, "TargetVMin");
}

bool NavMoveNearTarget::m38(f32* out) {
    auto* nav = mActor->m45();
    if (!nav)
        return false;
    *out = sead::Mathf::max(sub_71007320F0(mActor, *mWeaponIdx_s), nav->_2a8 * nav->_2ac) +
           *mReachTargetArea_s;
    return true;
}

}  // namespace uking::ai
