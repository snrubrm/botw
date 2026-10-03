#include "Game/AI/AI/aiNavMoveTargetWithJumpWater.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"

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

}  // namespace uking::ai
