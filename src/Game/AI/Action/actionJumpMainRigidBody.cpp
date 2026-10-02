#include "Game/AI/Action/actionJumpMainRigidBody.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::action {

JumpMainRigidBody::JumpMainRigidBody(const InitArg& arg) : ksys::act::ai::Action(arg) {}

JumpMainRigidBody::~JumpMainRigidBody() = default;

bool JumpMainRigidBody::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void JumpMainRigidBody::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void JumpMainRigidBody::leave_() {
    ksys::act::ai::Action::leave_();
}

void JumpMainRigidBody::loadParams_() {
    getStaticParam(&mPower_s, "Power");
    getStaticParam(&mVibrateStopCheck_s, "VibrateStopCheck");
    getStaticParam(&mVibrateCheckFrame_s, "VibrateCheckFrame");
    getStaticParam(&mVibrateMemoryStep_s, "VibrateMemoryStep");
    getStaticParam(&mIsRotJumpDir_s, "IsRotJumpDir");
    getStaticParam(&mPostBoundReactionKeys_s, "PostBoundReactionKeys");
    getStaticParam(&mJumpDir_s, "JumpDir");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getAITreeVariable(&mRefPosVibrateChecker_a, "RefPosVibrateChecker");
}

void JumpMainRigidBody::calc_() {
    ksys::act::ai::Action::calc_();
}

bool JumpMainRigidBody::isFinished() const {
    if (ActionBase::isFinished())
        return true;
    if (_78 || !_79)
        return false;
    auto* actor = mActor;
    if (isBgGroundHit(actor, false))
        return true;
    if (_7c && mActor->get68f())
        return true;
    return false;
}

}  // namespace uking::action
