#pragma once

#include <math/seadVector.h>
#include "Game/AI/AI/aiEnemyBaseArrowAttack.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WaistRotEnemyArrowAttack : public EnemyBaseArrowAttack {
    SEAD_RTTI_OVERRIDE(WaistRotEnemyArrowAttack, EnemyBaseArrowAttack)
public:
    explicit WaistRotEnemyArrowAttack(const InitArg& arg);
    ~WaistRotEnemyArrowAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void m37() override;

protected:
    // static_param at offset 0x50
    const int* mRandomPredictFrame_s{};
    sead::Vector3f _58{0, 0, 0};
    f32 _64 = 0;
};
KSYS_CHECK_SIZE_NX150(WaistRotEnemyArrowAttack, 0x68);

}  // namespace uking::ai
