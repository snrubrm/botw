#include "Game/AI/AI/aiStoneOctarockWait.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

// NON_MATCHING: store scheduling (the original stores the params before the callback members)
StoneOctarockWait::StoneOctarockWait(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StoneOctarockWait::~StoneOctarockWait() = default;

bool StoneOctarockWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StoneOctarockWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void StoneOctarockWait::leave_() {
    mActor->getDamageMgr()->removeDamageCallback(&_48);
}

void StoneOctarockWait::loadParams_() {
    getStaticParam(&mGuardEndTime_s, "GuardEndTime");
    getStaticParam(&mNoticeTerrorLevel_s, "NoticeTerrorLevel");
}

bool StoneOctarockWait::handleMessage_(const ksys::Message& message) {
    if (message.getType().value == 0x3000003 &&
        (isCurrentChild("ガード開始") || isCurrentChild("高速ガード開始"))) {
        _48._24 = false;
    }
    return false;
}

bool StoneOctarockWait::isChangeable() const {
    return getCurrentChild()->isChangeable() && isCurrentChild("通常");
}

}  // namespace uking::ai
