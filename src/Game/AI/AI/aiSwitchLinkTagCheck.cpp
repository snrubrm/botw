#include "Game/AI/AI/aiSwitchLinkTagCheck.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

SwitchLinkTagCheck::SwitchLinkTagCheck(const InitArg& arg) : SwitchAI(arg) {}

SwitchLinkTagCheck::~SwitchLinkTagCheck() = default;

bool SwitchLinkTagCheck::init_(sead::Heap* heap) {
    return SwitchAI::init_(heap);
}

void SwitchLinkTagCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    SwitchAI::enter_(params);
}

void SwitchLinkTagCheck::leave_() {
    SwitchAI::leave_();
}

void SwitchLinkTagCheck::loadParams_() {
    SwitchAI::loadParams_();
    getStaticParam(&mSignalType_s, "SignalType");
    getStaticParam(&mSetEnableJobTimerTiming_s, "SetEnableJobTimerTiming");
}

void SwitchLinkTagCheck::calc_() {
    SwitchAI::calc_();
}

bool SwitchLinkTagCheck::m34() {
    return mActor->checkBasicSig();
}

bool SwitchLinkTagCheck::m35() {
    auto* actor = mActor;
    if (isCurrentChild("オフ待機") || isCurrentChild("オフ"))
        return actor->checkBasicSig();
    return false;
}

bool SwitchLinkTagCheck::m36() {
    auto* actor = mActor;
    if (isCurrentChild("オン待機") || isCurrentChild("オン"))
        return !actor->checkBasicSig();
    return false;
}

bool SwitchLinkTagCheck::m37() {
    auto* child = getCurrentChild();
    return isCurrentChild("オン") && child->isFinished();
}

bool SwitchLinkTagCheck::m38() {
    auto* child = getCurrentChild();
    return isCurrentChild("オフ") && child->isFinished();
}

}  // namespace uking::ai
