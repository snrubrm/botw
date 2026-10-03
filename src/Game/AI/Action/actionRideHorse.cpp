#include "Game/AI/Action/actionRideHorse.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

RideHorse::RideHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RideHorse::~RideHorse() = default;

bool RideHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RideHorse::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void RideHorse::leave_() {
    if (auto* cc = mActor->getCharacterController())
        cc->sub_7100F60604();
    mActor->sub_71011DA834(&_90);
    if (!isFinished())
        sub_710023A4C8();
}

void RideHorse::loadParams_() {
    getStaticParam(&mJumpHeightOffset_s, "JumpHeightOffset");
    getStaticParam(&mMaxSpeed_s, "MaxSpeed");
    getStaticParam(&mFarRotSpeed_s, "FarRotSpeed");
    getStaticParam(&mNearRotSpeed_s, "NearRotSpeed");
    getStaticParam(&mRideRotSpeed_s, "RideRotSpeed");
    getStaticParam(&mLoopASInterpolateTime_s, "LoopASInterpolateTime");
    getStaticParam(&mPredictedRidePosOffset_s, "PredictedRidePosOffset");
    getStaticParam(&mPreRideSklRootOffset_s, "PreRideSklRootOffset");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

bool RideHorse::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x3000003) {
        mActor->sub_71011DA834(&_90);
        sub_710023A4C8();
    }
    return false;
}

void RideHorse::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
