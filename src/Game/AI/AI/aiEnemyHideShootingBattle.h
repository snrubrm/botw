#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class EnemyHideShootingBattle : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyHideShootingBattle, ksys::act::ai::Ai)
public:
    explicit EnemyHideShootingBattle(const InitArg& arg);
    ~EnemyHideShootingBattle() override;
    bool isChangeable() const override;
    bool isFailed() const override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x38
    sead::Vector3f* mTargetPos_d{};
    bool _40 = false;
    ksys::Timer _44{0, 0};
};

}  // namespace uking::ai
