#include "Game/AI/AI/aiPriestBossGiantDownSeq.h"

namespace uking::ai {

PriestBossGiantDownSeq::PriestBossGiantDownSeq(const InitArg& arg) : PriestBossMode(arg) {}

PriestBossGiantDownSeq::~PriestBossGiantDownSeq() = default;

bool PriestBossGiantDownSeq::init_(sead::Heap* heap) {
    return PriestBossMode::init_(heap);
}

void PriestBossGiantDownSeq::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossMode::enter_(params);
}

void PriestBossGiantDownSeq::leave_() {
    PriestBossMode::leave_();
}

void PriestBossGiantDownSeq::loadParams_() {
    PriestBossMode::loadParams_();
    getStaticParam(&mRecoverIfAlreadyDown_s, "RecoverIfAlreadyDown");
    getStaticParam(&mIsUseRecover_s, "IsUseRecover");
    getStaticParam(&mHitGroundASName_s, "HitGroundASName");
    getAITreeVariable(&mKeepDistFromGround_a, "KeepDistFromGround");
    getAITreeVariable(&mIsActive_a, "IsActive");
    getAITreeVariable(&mIsArrivedAtDestination_a, "IsArrivedAtDestination");
    getAITreeVariable(&mDestinationPos_a, "DestinationPos");
}



bool PriestBossGiantDownSeq::handleMessage_(const ksys::Message& message) {
    if (!_b0._30 && _b0.m2(message))
        return true;
    return false;
}

bool PriestBossGiantDownSeq::handleAck_(const ksys::MessageAck& ack) {
    if (!_80.sub_710070E070(ack))
        return false;
    _105 = true;
    return true;
}

}  // namespace uking::ai
