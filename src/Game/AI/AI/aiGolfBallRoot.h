#pragma once

#include <math/seadVector.h>
#include "Game/AI/aiUnk_71024f15c0.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GolfBallRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GolfBallRoot, ksys::act::ai::Ai)
public:
    explicit GolfBallRoot(const InitArg& arg);
    ~GolfBallRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mIntSmashJudgeFrame_s{};
    // static_param at offset 0x40
    const int* mIntSmashContinueFrame_s{};
    // static_param at offset 0x48
    const float* mFloatJudgeSmash_s{};
    // static_param at offset 0x50
    const float* mFloatJudgeStop_s{};
    sead::Vector3f _58 = sead::Vector3f::zero;
    bool _64 = false;
    bool _65 = false;
    u32 _68 = 0;
    bool _6c = false;
    u32 _70 = 0;
    sead::Vector3f _74 = sead::Vector3f::zero;
    Unk_71024f15c0 _80;
    bool _e0 = false;
    f32 _e4 = 1.0f;
    sead::Vector3f _e8 = sead::Vector3f::zero;
    sead::Vector3f _f4 = sead::Vector3f::zero;
    sead::Vector3f _100 = sead::Vector3f::zero;
    sead::Vector3f _10c = sead::Vector3f::zero;
};
KSYS_CHECK_SIZE_NX150(GolfBallRoot, 0x118);

}  // namespace uking::ai
