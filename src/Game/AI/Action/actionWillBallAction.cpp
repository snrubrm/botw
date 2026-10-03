#include "Game/AI/Action/actionWillBallAction.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

// NON_MATCHING: regalloc (keeps &_7c in x20 across the memset)
WillBallAction::WillBallAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WillBallAction::~WillBallAction() = default;

bool WillBallAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WillBallAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WillBallAction::leave_() {
    if (auto* body = mActor->getMainBody())
        body->setGravityFactor(_88);
}

void WillBallAction::loadParams_() {
    getStaticParam(&mParams.mRotBaseRatio_s, "RotBaseRatio");
    getStaticParam(&mParams.mMaxSpeed_s, "MaxSpeed");
    getStaticParam(&mParams.mRotSpeed_s, "RotSpeed");
    getStaticParam(&mParams.mReachRange_s, "ReachRange");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
    getStaticParam(&mParams.mTiredAngle_s, "TiredAngle");
    getStaticParam(&mParams.mIsIgnoreLastSpRot_s, "IsIgnoreLastSpRot");
    getStaticParam(&mParams.mIsAddAABBHeight_s, "IsAddAABBHeight");
    getStaticParam(&mParams.mIsGround_s, "IsGround");
    getStaticParam(&mParams.mAccel_s, "Accel");
}

void WillBallAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
