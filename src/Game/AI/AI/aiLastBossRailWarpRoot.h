#pragma once

#include "Game/AI/AI/aiLastBossNormalWarpRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LastBossRailWarpRoot : public LastBossNormalWarpRoot {
    SEAD_RTTI_OVERRIDE(LastBossRailWarpRoot, LastBossNormalWarpRoot)
public:
    explicit LastBossRailWarpRoot(const InitArg& arg);
    ~LastBossRailWarpRoot() override;

    void loadParams_() override;
    void m35(ksys::act::ai::InlineParamPack* params) override;

protected:
    // dynamic_param at offset 0x80
    int* mRailIndex_d{};
};

}  // namespace uking::ai
