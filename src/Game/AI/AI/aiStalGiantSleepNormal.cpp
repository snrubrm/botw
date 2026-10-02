#include "Game/AI/AI/aiStalGiantSleepNormal.h"
#include <prim/seadScopedLock.h>

namespace uking::ai {

StalGiantSleepNormal::StalGiantSleepNormal(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StalGiantSleepNormal::~StalGiantSleepNormal() = default;

bool StalGiantSleepNormal::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StalGiantSleepNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void StalGiantSleepNormal::leave_() {
    ksys::act::ai::Ai::leave_();
}

void StalGiantSleepNormal::loadParams_() {
    getStaticParam(&mAwakeDelayTime_s, "AwakeDelayTime");
    getStaticParam(&mIsAwakenByHearing_s, "IsAwakenByHearing");
    getStaticParam(&mIsWaitAfterAwaken_s, "IsWaitAfterAwaken");
}

bool StalGiantSleepNormal::isChangeable() const {
    return isCurrentChild("待機");
}

bool StalGiantSleepNormal::handleMessage_(const ksys::Message& message) {
    if (isCurrentChild("退散") || _60._30)
        return false;
    return _60.m2(message);
}

}  // namespace uking::ai

// Defined in this TU in the original (inlined into StalGiantSleepNormal::handleMessage_).
bool Unk_7102424730::m2(const ksys::Message& message) {
    if (message.getType().value != 0x80000b8)
        return false;

    auto* payload = static_cast<Unk_71023c5480_Payload*>(message.getUserData());
    if (!payload)
        return false;

    payload->x(&_38.mLink);
    _30 = true;
    _18 = message.getSource();
    return true;
}

