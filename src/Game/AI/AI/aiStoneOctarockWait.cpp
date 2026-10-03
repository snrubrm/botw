#include "Game/AI/AI/aiStoneOctarockWait.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

// NON_MATCHING: store scheduling (the original stores the params before the callback members)
StoneOctarockWait::StoneOctarockWait(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StoneOctarockWait::~StoneOctarockWait() = default;

bool StoneOctarockWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the original tests RootAi::_16e bit 1 inline (an inline-only ActionBase accessor?); ours calls the
// out-of-line testRootAiFlag2
void StoneOctarockWait::enter_(ksys::act::ai::InlineParamPack* params) {
    const s32 guard_end_time = *mGuardEndTime_s;
    _70 = guard_end_time;
    _74 = guard_end_time;
    _78 = guard_end_time;

    if (!testRootAiFlag2(ksys::act::ai::RootAiFlag2::_1)) {
        auto* awareness = mActor->getAwareness();
        if (awareness && awareness->_260[2]) {
            const auto* entries = &awareness->_260[2]->_8;
            if (entries->size() >= 1) {
                auto* entry = ksys::act::sub_7100D78E30(entries, 0);
                if (entry && entry->_a4 >= *mNoticeTerrorLevel_s) {
                    if (!_48.mDamageManager)
                        mActor->getDamageMgr()->addDamageCallback(4, &_48);
                    changeChild("高速ガード開始", params);
                    return;
                }
            }
        }
        changeChild("通常", params);
    } else {
        if (!_48.mDamageManager)
            mActor->getDamageMgr()->addDamageCallback(4, &_48);
        changeChild("ガード待機", params);
    }
}

void StoneOctarockWait::leave_() {
    mActor->getDamageMgr()->removeDamageCallback(&_48);
}

void StoneOctarockWait::loadParams_() {
    getStaticParam(&mGuardEndTime_s, "GuardEndTime");
    getStaticParam(&mNoticeTerrorLevel_s, "NoticeTerrorLevel");
}

bool StoneOctarockWait::handleMessage_(const ksys::Message& message) {
    if (message.getType() == 0x3000003 &&
        (isCurrentChild("ガード開始") || isCurrentChild("高速ガード開始"))) {
        _48._24 = false;
    }
    return false;
}

bool StoneOctarockWait::isChangeable() const {
    return getCurrentChild()->isChangeable() && isCurrentChild("通常");
}

}  // namespace uking::ai
