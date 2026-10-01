#include "Game/AI/AI/aiSwitchHit.h"

namespace uking::ai {

SwitchHit::SwitchHit(const InitArg& arg) : SwitchAI(arg) {}

SwitchHit::~SwitchHit() = default;

bool SwitchHit::init_(sead::Heap* heap) {
    return SwitchAI::init_(heap);
}

void SwitchHit::enter_(ksys::act::ai::InlineParamPack* params) {
    SwitchAI::enter_(params);
    _40 = *mWaitTime_s;
    _44 = false;
    _45 = false;
}

void SwitchHit::leave_() {
    SwitchAI::leave_();
}

void SwitchHit::loadParams_() {
    SwitchAI::loadParams_();
    getStaticParam(&mWaitTime_s, "WaitTime");
}

bool SwitchHit::m35() {
    return isCurrentChild("オフ待機") && _44 && _45;
}

bool SwitchHit::m36() {
    return isCurrentChild("オン待機") && _44 && _45;
}

bool SwitchHit::m37() {
    auto* child = getCurrentChild();
    return isCurrentChild("オン") && child->isChangeable();
}

bool SwitchHit::m38() {
    auto* child = getCurrentChild();
    return isCurrentChild("オフ") && child->isChangeable();
}

void SwitchHit::m40() {
    _40 = 0;
    changeChild("オフ待機");
}

void SwitchHit::m41() {
    _40 = 0;
    changeChild("オン待機");
}

void SwitchHit::m42() {
    changeChild("オフ");
}

void SwitchHit::m43() {
    changeChild("オン");
}

}  // namespace uking::ai
