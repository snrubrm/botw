#include "Game/AI/AI/aiNavMoveTargetWithJumpWater.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

NavMoveTargetWithJumpWater::NavMoveTargetWithJumpWater(const InitArg& arg) : NavMoveTarget(arg) {}

NavMoveTargetWithJumpWater::~NavMoveTargetWithJumpWater() = default;

bool NavMoveTargetWithJumpWater::init_(sead::Heap* heap) {
    return NavMoveTarget::init_(heap);
}

void NavMoveTargetWithJumpWater::enter_(ksys::act::ai::InlineParamPack* params) {
    NavMoveTarget::enter_(params);
}

void NavMoveTargetWithJumpWater::leave_() {
    NavMoveTarget::leave_();
}

bool NavMoveTargetWithJumpWater::m36() {
    auto* actor = mActor;
    if (!actor)
        return false;
    f32 depth = 0.0f;
    if (actor->get68f()) {
        const f32 y = actor->getMtx().getTranslation().y;
        depth = actor->get6f0() - y;
    }
    if (depth >= *mInWaterDepth_s)
        return sub_710072F8E4(actor, *m34(), nullptr, 3.0f);
    return NavMoveTarget::m36();
}

void NavMoveTargetWithJumpWater::loadParams_() {
    NavMoveTarget::loadParams_();
    getStaticParam(&mJumpDist_s, "JumpDist");
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mWaterCheckDist_s, "WaterCheckDist");
    getStaticParam(&mIsCheckDamage_s, "IsCheckDamage");
}

// NON_MATCHING: the parameter pack and vector/string temporaries use different stack slots.
void NavMoveTargetWithJumpWater::calc_() {
    NavMoveTarget::calc_();
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed() || !child->isChangeable())
        return;
    if (!isCurrentChild("移動") && !isCurrentChild("直進"))
        return;
    const f32 check_dist = *mWaterCheckDist_s;
    sead::Vector3f check_position;
    sub_71004BA408(&check_position, check_dist < 0.0f ? *mJumpDist_s : check_dist);
    if (!sub_71004BA1F8(check_position))
        return;
    sead::Vector3f jump_position;
    sub_71004BA408(&jump_position, *mJumpDist_s);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(jump_position, "TargetPos", -1);
    changeChild("ジャンプ", &pack);
}

}  // namespace uking::ai
