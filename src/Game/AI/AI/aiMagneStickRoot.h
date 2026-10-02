#pragma once

#include <math/seadMathCalcCommon.h>

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MagneStickRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(MagneStickRoot, ksys::act::ai::Ai)
public:
    explicit MagneStickRoot(const InitArg& arg);
    ~MagneStickRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    u32 _38 = 0;
    // static_param at offset 0x40
    const float* mDefaultConnectionDistance_s{};
    // static_param at offset 0x48
    const float* mCollideRadiusFactor_s{};
    // map_unit_param at offset 0x50
    const float* mCollideRadius_m{};
    // map_unit_param at offset 0x58
    const bool* mJoinSystemGroup_m{};
    // map_unit_param at offset 0x60
    const bool* mRegistFromBeginning_m{};
    // map_unit_param at offset 0x68
    const bool* mIgnoreObstacle_m{};
    // aitree_variable at offset 0x70
    bool* mIsTargetFixedAcceptor_a{};
    bool _78 = false;
    bool _79 = false;
    u32 _7c = 0;
    f32 _80 = 0.0f;
    f32 _84 = 0.0f;
    f32 _88 = sead::Mathf::maxNumber();
    f32 _8c = 0.0f;
    u32 _90 = 0;
    u32 _94 = 0;
    u32 _98 = 0;
    u32 _9c = 0;
};

}  // namespace uking::ai
