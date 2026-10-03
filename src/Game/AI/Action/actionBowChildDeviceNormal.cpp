#include "Game/AI/Action/actionBowChildDeviceNormal.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

BowChildDeviceNormal::BowChildDeviceNormal(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BowChildDeviceNormal::~BowChildDeviceNormal() = default;

bool BowChildDeviceNormal::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BowChildDeviceNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    // NON_MATCHING: the original stores _d0/_d4 as one 64-bit immediate and schedules the _cc store later
    _c8 = 0;
    sub_710073FA90(&_a0, mActor);
    _88 = 0.0f;
    _8c = 0.0f;
    _90 = -1.0f;
    _cc = false;
    const f32 wait_time = *mWaitTime_s;
    _98 = wait_time;
    _9c = -1.0f;
    _94 = wait_time;
    _d0 = 0;
    _d4 = 1;
    playAS("Close", false, 0, 0, -1.0f);
    if (auto* body = mActor->getMainBody())
        body->setContactNone();
    if (auto* body = mActor->getTgtBody())
        body->setContactNone();
}

void BowChildDeviceNormal::leave_() {
    ksys::act::ai::Action::leave_();
}

void BowChildDeviceNormal::loadParams_() {
    getStaticParam(&mMoveSpeed_s, "MoveSpeed");
    getStaticParam(&mWaitTime_s, "WaitTime");
    getStaticParam(&mAccelRate_s, "AccelRate");
    getStaticParam(&mBrakeStartDist_s, "BrakeStartDist");
    getStaticParam(&mVibrationSpeed_s, "VibrationSpeed");
    getStaticParam(&mStopDist_s, "StopDist");
    getStaticParam(&mVibrationLength_s, "VibrationLength");
    getStaticParam(&mMoveTime_s, "MoveTime");
    getStaticParam(&mIsMoveAccel_s, "IsMoveAccel");
    getDynamicParam(&mID_d, "ID");
    getDynamicParam(&mXRotateAngle_d, "XRotateAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mParentActor_d, "ParentActor");
}

void BowChildDeviceNormal::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
