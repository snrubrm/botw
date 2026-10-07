#pragma once

#include <math/seadVector.h>

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DragonTurn : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DragonTurn, ksys::act::ai::Ai)
public:
    explicit DragonTurn(const InitArg& arg);
    ~DragonTurn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void sub_7100371E4C();
    bool sub_7100372E30(sead::Vector3f* target, const sead::Vector3f* front);
protected:
    // static_param at offset 0x38
    const float* mSpeed_s{};
    // static_param at offset 0x40
    const float* mAvoidStartDistance_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetVec_d{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
    f32 _58 = 0;
    f32 _5c = 0;
    f32 _60 = 0;
    sead::Vector3f _64 = sead::Vector3f::ex;
    f32 _70 = 0.0f;
    f32 _74 = -1.0f;
    sead::Vector3f _78 = sead::Vector3f::zero;
    f32 _84 = 0;
};

}  // namespace uking::ai
