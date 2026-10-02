#include "Game/AI/Action/actionKnockBackShock.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::action {

KnockBackShock::KnockBackShock(const InitArg& arg) : ksys::act::ai::Action(arg) {}

KnockBackShock::~KnockBackShock() = default;

bool KnockBackShock::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void KnockBackShock::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void KnockBackShock::leave_() {
    ksys::act::ai::Action::leave_();
}

void KnockBackShock::loadParams_() {
    getStaticParam(&mHitImpactForce_s, "HitImpactForce");
    getStaticParam(&mVelReduce_s, "VelReduce");
    getStaticParam(&mVelReduceOnGround_s, "VelReduceOnGround");
}

void KnockBackShock::calc_() {
    if (isFinished() || isFailed())
        return;
    auto* actor = mActor;
    auto* controller = actor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    if (isBgGroundHit(actor, false))
        sub_7100737C0C(controller, *mVelReduceOnGround_s, -sead::Vector3f::ey);
    else
        sub_7100737C0C(controller, *mVelReduce_s, -sead::Vector3f::ey);
}

}  // namespace uking::action
