#include "Game/AI/AI/aiStoneOctarockGuardNearTarget.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
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

void StoneOctarockGuardNearTarget::calc_() {
    if (_b8) {
        if (isCurrentChild("ガード開始") || isCurrentChild("高速ガード開始"))
            _60._24 = !isSlowTimeMaybe() && mActor->getConnectedCalcChild() != nullptr;
        else
            _60._24 = true;
    }
    TimedGuardNearTarget::calc_();
}

bool StoneOctarockGuardNearTarget::m39(float distance) {
    if (!TimedGuardNearTarget::m39(distance))
        return false;
    auto* awareness = mActor->getAwareness();
    if (awareness && awareness->_260[2]) {
        const auto* entries = &awareness->_260[2]->_8;
        if (entries->size() >= 1) {
            auto* entry = ksys::act::sub_7100D78E30(entries, 0);
            if (entry && entry->_a4 >= *mNoticeTerrorLevel_s)
                return false;
        }
    }
    return true;
}

}  // namespace uking::ai
