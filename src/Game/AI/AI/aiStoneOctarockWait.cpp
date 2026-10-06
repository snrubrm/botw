#include "Game/AI/AI/aiStoneOctarockWait.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/System/Timer.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

StoneOctarockWait::StoneOctarockWait(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StoneOctarockWait::~StoneOctarockWait() = default;

bool StoneOctarockWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the original tests RootAi::_16e bit 1 inline (an inline-only ActionBase accessor?); ours calls the
// out-of-line testRootAiFlag2
void StoneOctarockWait::enter_(ksys::act::ai::InlineParamPack* params) {
    const s32 guard_end_time = *mParams.mGuardEndTime_s;
    _70 = guard_end_time;
    _74 = guard_end_time;
    _78 = guard_end_time;

    if (!testRootAiFlag2(ksys::act::ai::RootAiFlag2::_1)) {
        auto* awareness = mActor->getAwareness();
        if (awareness && awareness->_260[2]) {
            const auto* entries = &awareness->_260[2]->_8;
            if (entries->size() >= 1) {
                auto* entry = ksys::act::sub_7100D78E30(entries, 0);
                if (entry && entry->_a4 >= *mParams.mNoticeTerrorLevel_s) {
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

bool StoneOctarockWait::isTerrorNoticed() const {
    auto* awareness = mActor->getAwareness();
    if (awareness && awareness->_260[2]) {
        const auto* entries = &awareness->_260[2]->_8;
        if (entries->size() >= 1) {
            auto* entry = ksys::act::sub_7100D78E30(entries, 0);
            if (entry && entry->_a4 >= *mParams.mNoticeTerrorLevel_s)
                return true;
        }
    }
    return false;
}

// NON_MATCHING: same instructions, but clang hoists &_48 (the damage callback) into a callee-saved register instead
// of &_70, so the register assignment differs.
void StoneOctarockWait::calc_() {
    bool flag = true;
    if (isCurrentChild("ガード開始") || isCurrentChild("高速ガード開始"))
        flag = !(isSlowTimeMaybe() || !mActor->getConnectedCalcChild());
    _48._24 = flag;

    if (isTerrorNoticed())
        _70 = _74 == _78 ? _74 : sead::GlobalRandom::instance()->getS32Range(_74, _78);
    else
        ksys::Timer::update(&_70, -1.0f);

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("高速ガード開始")) {
            auto* damage_mgr = mActor->getDamageMgr();
            if (!_48.mDamageManager)
                damage_mgr->addDamageCallback(4, &_48);
            changeChild("ガード待機");
        } else if (isCurrentChild("ガード待機")) {
            mActor->getDamageMgr()->removeDamageCallback(&_48);
            changeChild("ガード終了");
        } else if (isCurrentChild("ガード終了")) {
            changeChild("通常");
        } else if (child->isFinished()) {
            setFinished();
        } else {
            setFailed();
        }
    } else if (child->isChangeable()) {
        if (isCurrentChild("通常") || isCurrentChild("ガード終了")) {
            if (isTerrorNoticed()) {
                auto* damage_mgr = mActor->getDamageMgr();
                if (!_48.mDamageManager)
                    damage_mgr->addDamageCallback(4, &_48);
                changeChild("高速ガード開始");
            }
        } else if (isCurrentChild("ガード待機") && _70 <= 0.0f) {
            mActor->getDamageMgr()->removeDamageCallback(&_48);
            changeChild("ガード終了");
        }
    }
}

void StoneOctarockWait::leave_() {
    mActor->getDamageMgr()->removeDamageCallback(&_48);
}

void StoneOctarockWait::loadParams_() {
    getStaticParam(&mParams.mGuardEndTime_s, "GuardEndTime");
    getStaticParam(&mParams.mNoticeTerrorLevel_s, "NoticeTerrorLevel");
}

bool StoneOctarockWait::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x3000003 &&
        (isCurrentChild("ガード開始") || isCurrentChild("高速ガード開始"))) {
        _48._24 = false;
    }
    return false;
}

bool StoneOctarockWait::isChangeable() const {
    return getCurrentChild()->isChangeable() && isCurrentChild("通常");
}

}  // namespace uking::ai
