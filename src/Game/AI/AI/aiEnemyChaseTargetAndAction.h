#pragma once

#include "Game/AI/AI/aiUnarmedEnemySearch.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class EnemyChaseTargetAndAction : public UnarmedEnemySearch {
    SEAD_RTTI_OVERRIDE(EnemyChaseTargetAndAction, UnarmedEnemySearch)
public:
    explicit EnemyChaseTargetAndAction(const InitArg& arg);
    ~EnemyChaseTargetAndAction() override;
    bool isChangeable() const override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    // 0x7100384d50 (placeholder name): the target is within reach (ReachTargetArea + weapon range)
    // or among the actor's sensed actors.
    bool sub_7100384D50();

    void m37() override;
    void m38() override;
    void m39() override;

protected:
    // static_param at offset 0x68
    const int* mRepathTime_s{};
    // static_param at offset 0x70
    const float* mLostDist_s{};
    // static_param at offset 0x78
    const float* mLostSpeed_s{};
    // static_param at offset 0x80
    const float* mLostAng_s{};
    // dynamic_param at offset 0x88
    ksys::act::BaseProcLink* mTargetActor_d{};
    ksys::Timer _90{0, 0};
};

}  // namespace uking::ai
