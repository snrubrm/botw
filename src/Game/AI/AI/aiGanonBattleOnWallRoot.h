#pragma once

#include <math/seadVector.h>

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class GanonBattleOnWallRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GanonBattleOnWallRoot, ksys::act::ai::Ai)
public:
    explicit GanonBattleOnWallRoot(const InitArg& arg);
    ~GanonBattleOnWallRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mGuardianActivateHP_s{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mTargetPos_d{};
    sead::Vector3f _48;
    s32 _54{};
    s32 _58{};
    s32 _5c{};
    ksys::Timer _60;
};

}  // namespace uking::ai
