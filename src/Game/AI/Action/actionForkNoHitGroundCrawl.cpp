#include "Game/AI/Action/actionForkNoHitGroundCrawl.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkNoHitGroundCrawl::ForkNoHitGroundCrawl(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkNoHitGroundCrawl::~ForkNoHitGroundCrawl() = default;

bool ForkNoHitGroundCrawl::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkNoHitGroundCrawl::enter_(ksys::act::ai::InlineParamPack* params) {
    const auto& vel = mActor->getVelocity();
    const f32 speed = sead::Mathf::sqrt(vel.x * vel.x + vel.z * vel.z);
    _38.value = speed;
    _38.prev_value = speed;
    mFlags.set(Flag::Changeable);
}

void ForkNoHitGroundCrawl::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkNoHitGroundCrawl::loadParams_() {
    getStaticParam(&mMaxSpeed_s, "MaxSpeed");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mEndRadius_s, "EndRadius");
}

void ForkNoHitGroundCrawl::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
