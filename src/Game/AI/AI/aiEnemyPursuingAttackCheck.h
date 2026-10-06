#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class EnemyPursuingAttackCheck : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyPursuingAttackCheck, ksys::act::ai::Ai)
public:
    explicit EnemyPursuingAttackCheck(const InitArg& arg);
    ~EnemyPursuingAttackCheck() override;
    bool isFailed() const override;
    bool isFinished() const override;
    bool isChangeable() const override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    // 0x71003a90d8 (placeholder name)
    bool sub_71003A90D8();
    // 0x71003a92ac (placeholder name)
    void changeToFollowUpAttack();

protected:
    // static_param at offset 0x38
    const int* mPursuingAttackInterval_s{};
    // static_param at offset 0x40
    const int* mPursuingAttackIntervalRand_s{};
    // static_param at offset 0x48
    const float* mPursuingAttackStartAng_s{};
    // static_param at offset 0x50
    const float* mAttackAng_s{};
    ksys::Timer _58{0, 0};
};

}  // namespace uking::ai
