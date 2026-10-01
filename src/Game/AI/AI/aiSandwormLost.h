#pragma once

#include "Game/AI/AI/aiEnemyLost.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SandwormLost : public EnemyLost {
    SEAD_RTTI_OVERRIDE(SandwormLost, EnemyLost)
public:
    explicit SandwormLost(const InitArg& arg);
    ~SandwormLost() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void m34() override;

protected:
    // static_param at offset 0x60
    const float* mDiveSandOffset_s{};
    bool _68 = false;
};
KSYS_CHECK_SIZE_NX150(SandwormLost, 0x70);

}  // namespace uking::ai
