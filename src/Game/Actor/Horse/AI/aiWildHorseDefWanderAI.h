#pragma once

#include <random/seadGlobalRandom.h>
#include "Game/gameWildHorseMgr.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WildHorseDefWanderAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WildHorseDefWanderAI, ksys::act::ai::Ai)
public:
    explicit WildHorseDefWanderAI(const InitArg& arg);
    ~WildHorseDefWanderAI() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void calc_() override;

private:
    // inline-only in the original; name is a guess (calc_ repeats it three times): a random wait time, state 0,
    // releases the WildHorseMgr slot (as leave_) and starts "待機".
    void startWait(WildHorseMgr* mgr) {
        const f32 min = *mMinWaitTime_s;
        const f32 max = *mMaxWaitTime_s;
        _50 = sead::GlobalRandom::instance()->getF32Range(min, max);
        _56 = 0;
        if (mgr && _54.slot >= 0) {
            if (mgr->mSlots[_54.slot].client == &_54) {
                mgr->mSlots[_54.slot].client = nullptr;
                mgr->mSlots[_54.slot].timer = 0;
            } else {
                _54.slot = -1;
            }
        }
        changeChild("待機");
    }

protected:

protected:
    // static_param at offset 0x38
    const float* mChangeWaitRate_s{};
    // static_param at offset 0x40
    const float* mMaxWaitTime_s{};
    // static_param at offset 0x48
    const float* mMinWaitTime_s{};
    f32 _50 = 0;
    /* 0x54 */ WildHorseMgr::Client _54{-1, -1};  // priority, slot
    s8 _56 = 0;
};
KSYS_CHECK_SIZE_NX150(WildHorseDefWanderAI, 0x58);

}  // namespace uking::ai
