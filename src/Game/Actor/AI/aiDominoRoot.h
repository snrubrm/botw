#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DominoRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DominoRoot, ksys::act::ai::Ai)
public:
    explicit DominoRoot(const InitArg& arg);
    ~DominoRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    // 0x7100366388 (placeholder name)
    void changeToFall(const sead::Vector3f& vel, const sead::Vector3f& ang_vel);

protected:
    // static_param at offset 0x38
    const float* mPointVelTh_s{};
    // static_param at offset 0x40
    const float* mLinearRate_s{};
    // static_param at offset 0x48
    const float* mAngRate_s{};
    // static_param at offset 0x50
    const float* mCheckHeightRate_s{};
    // static_param at offset 0x58
    const float* mFriction_s{};
    // static_param at offset 0x60
    const bool* mIsIgnoreWater_s{};
    // map_unit_param at offset 0x68
    const bool* mIsBreakable_m{};
    // map_unit_param at offset 0x70
    const bool* mEnableToEmitSpEffect_m{};
    f32 _78{};
    int _7c{};
    bool _80{};
};

}  // namespace uking::ai
