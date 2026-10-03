#pragma once

#include "Game/AI/AI/aiGuardianMiniBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianMini2ndBattle : public GuardianMiniBattle {
    SEAD_RTTI_OVERRIDE(GuardianMini2ndBattle, GuardianMiniBattle)
public:
    explicit GuardianMini2ndBattle(const InitArg& arg);
    ~GuardianMini2ndBattle() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

    void m44(ksys::act::ai::InlineParamPack* params) override;
    bool m45() override;

protected:
    // static_param at offset 0x1b8
    const int* mAttackHitNum_s{};
    // static_param at offset 0x1c0
    const int* mCounterStopTime_s{};
    s32 _1c8 = 0;
    bool _1cc = true;
    ksys::Timer _1d0{0, 0};
};
KSYS_CHECK_SIZE_NX150(GuardianMini2ndBattle, 0x1e0);

}  // namespace uking::ai
