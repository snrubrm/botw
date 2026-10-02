#include "Game/AI/Action/actionStopJump.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::action {

StopJump::StopJump(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

StopJump::~StopJump() = default;

bool StopJump::init_(sead::Heap* heap) {
    return ActionWithPosAngReduce::init_(heap);
}

void StopJump::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
    _58 = 0;
}

void StopJump::leave_() {
    ActionWithPosAngReduce::leave_();
}

void StopJump::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mJumpLoopAS_s, "JumpLoopAS");
    getStaticParam(&mLandingAS_s, "LandingAS");
}

void StopJump::calc_() {
    ActionWithPosAngReduce::calc_();
}

bool StopJump::isFinished() const {
    if (ksys::act::ai::Action::isFinished())
        return true;
    if (_58 != 1 || !mLandingAS_s.isEmpty())
        return false;
    return isBgGroundHit(mActor, false) || sub_71005E1064(mActor);
}

}  // namespace uking::action
