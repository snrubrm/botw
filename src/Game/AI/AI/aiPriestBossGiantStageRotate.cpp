#include "Game/AI/AI/aiPriestBossGiantStageRotate.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

PriestBossGiantStageRotate::PriestBossGiantStageRotate(const InitArg& arg) : PriestBossMode(arg) {}

PriestBossGiantStageRotate::~PriestBossGiantStageRotate() = default;

bool PriestBossGiantStageRotate::init_(sead::Heap* heap) {
    return PriestBossMode::init_(heap);
}

void PriestBossGiantStageRotate::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossMode::enter_(params);
    _140.makeAllZero();
    if (!*mSendOnThrowASEvent_s)
        sub_710051C210();

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    if (*mIsUseStartAction_s)
        changeChild("開始", &pack);
    else
        changeChild("回転終了待機", &pack);
}

void PriestBossGiantStageRotate::leave_() {
    PriestBossMode::leave_();
}

void PriestBossGiantStageRotate::loadParams_() {
    PriestBossMode::loadParams_();
    getStaticParam(&mSendCommand_s, "SendCommand");
    getStaticParam(&mSendOnThrowASEvent_s, "SendOnThrowASEvent");
    getStaticParam(&mIsUseStartAction_s, "IsUseStartAction");
}

bool PriestBossGiantStageRotate::handleMessage_(const ksys::Message& message) {
    if (!_88._30 && _88.m2(message))
        return true;
    return false;
}

// NON_MATCHING: operand order of the orr in setBit (same as PriestBossIronBallRoot::m41)
bool PriestBossGiantStageRotate::handleAck_(const ksys::MessageAck& ack) {
    if (!_58.sub_710070E070(ack))
        return false;
    _140.setBit(Flag(Flag::_6));
    return true;
}

}  // namespace uking::ai
