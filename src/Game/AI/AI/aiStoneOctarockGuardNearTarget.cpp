#include "Game/AI/AI/aiStoneOctarockGuardNearTarget.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

StoneOctarockGuardNearTarget::StoneOctarockGuardNearTarget(const InitArg& arg)
    : TimedGuardNearTarget(arg) {}

StoneOctarockGuardNearTarget::~StoneOctarockGuardNearTarget() = default;

bool StoneOctarockGuardNearTarget::init_(sead::Heap* heap) {
    return TimedGuardNearTarget::init_(heap);
}

void StoneOctarockGuardNearTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    _b8 = false;
    TimedGuardNearTarget::enter_(params);
}

void StoneOctarockGuardNearTarget::leave_() {
    TimedGuardNearTarget::leave_();
}

void StoneOctarockGuardNearTarget::loadParams_() {
    TimedGuardNearTarget::loadParams_();
    getStaticParam(&mNoticeTerrorLevel_s, "NoticeTerrorLevel");
}

bool StoneOctarockGuardNearTarget::handleMessage_(const ksys::Message& message) {
    if (message.getType().value == 0x3000003 &&
        (isCurrentChild("ガード開始") || isCurrentChild("高速ガード開始"))) {
        _60._24 = false;
    }
    return false;
}

void StoneOctarockGuardNearTarget::m37(bool enable) {
    _b8 = enable;
    GuardNearTarget::m37(enable);
}

}  // namespace uking::ai
