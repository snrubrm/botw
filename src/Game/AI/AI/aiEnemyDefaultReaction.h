#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyDefaultReaction : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyDefaultReaction, ksys::act::ai::Ai)
public:
    explicit EnemyDefaultReaction(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool isChangeable() const override;

protected:
    // static_param at offset 0x38
    const int* mJustGuardTimesMin_s{};
    // static_param at offset 0x40
    const int* mJustGuardTimesMax_s{};
    // static_param at offset 0x48
    const int* mSmallDamageCancelTimes_s{};
    // static_param at offset 0x50
    const bool* mInComboSmallDamageNoCancel_s{};
    int _58{};
    int _5c{};
    bool _60{};
    bool _61{};
    bool _62 = true;
};

}  // namespace uking::ai
