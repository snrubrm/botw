#include "Game/Actor/Horse/AI/aiWildHorseDefWanderAI.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/System/Timer.h"

namespace uking::ai {

WildHorseDefWanderAI::WildHorseDefWanderAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WildHorseDefWanderAI::~WildHorseDefWanderAI() = default;

bool WildHorseDefWanderAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WildHorseDefWanderAI::enter_(ksys::act::ai::InlineParamPack* params) {
    const f32 min = *mMinWaitTime_s;
    const f32 max = *mMaxWaitTime_s;
    _50 = sead::GlobalRandom::instance()->getF32Range(min, max);
    _56 = 0;
    changeChild("待機");
}

void WildHorseDefWanderAI::leave_() {
    auto* mgr = WildHorseMgr::instance();
    if (!mgr)
        return;
    if (_54.slot < 0)
        return;
    if (mgr->mSlots[_54.slot].client == &_54) {
        mgr->mSlots[_54.slot].client = nullptr;
        mgr->mSlots[_54.slot].timer = 0;
    } else {
        _54.slot = -1;
    }
}

// NON_MATCHING: the original tests the state as 2, 1, then 0 (ldrsb; ours tests 0 first) and allocates other registers
// Alternates between waiting ("待機", for a random time) and moving ("移動"); moving needs one of the
// WildHorseMgr slots.
void WildHorseDefWanderAI::calc_() {
    auto* mgr = WildHorseMgr::instance();
    auto* child = getCurrentChild();
    ksys::Timer::update(&_50, -1.0f);

    if (!child || child->isFinished() || child->isFailed()) {
        if (mgr && !mgr->requestSlot(&_54)) {
            startWait(mgr);
            return;
        }
        const f32 rate = *mChangeWaitRate_s;
        if (sead::GlobalRandom::instance()->getF32() < rate) {
            startWait(mgr);
            return;
        }
        _56 = 2;
        changeChild("移動");
        return;
    }

    if (!child->isChangeable())
        return;

    switch (_56) {
    case 2:
        if (!mgr || mgr->requestSlot(&_54))
            return;
        startWait(mgr);
        return;
    case 1:
        if (mgr && !mgr->requestSlot(&_54))
            return;
        break;
    case 0: {
        if (!(_50 <= 0.0f))
            return;
        const f32 rate = *mChangeWaitRate_s / 5.0f;
        if (sead::GlobalRandom::instance()->getF32() < rate) {
            const f32 min = *mMinWaitTime_s;
            const f32 max = *mMaxWaitTime_s;
            _50 = sead::GlobalRandom::instance()->getF32Range(min, max);
            return;
        }
        if (mgr) {
            mgr->requestSlot(&_54);
            _56 = 1;
            return;
        }
        break;
    }
    default:
        return;
    }

    _56 = 2;
    changeChild("移動");
}

void WildHorseDefWanderAI::loadParams_() {
    getStaticParam(&mChangeWaitRate_s, "ChangeWaitRate");
    getStaticParam(&mMaxWaitTime_s, "MaxWaitTime");
    getStaticParam(&mMinWaitTime_s, "MinWaitTime");
}

}  // namespace uking::ai
