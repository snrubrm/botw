#pragma once

#include "Game/AI/Action/actionRotateTurnToTarget.h"
#include "Game/AI/aiUnk_71025b0578.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BackFlip : public RotateTurnToTarget {
    SEAD_RTTI_OVERRIDE(BackFlip, RotateTurnToTarget)
public:
    explicit BackFlip(const InitArg& arg);
    ~BackFlip() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isFinished() const override;

protected:
    void calc_() override;

    // aitree_variable at offset 0x78
    void* mRefPosVibrateChecker_a{};
    // static_param at offset 0x80
    const float* mSpeed_s{};
    // static_param at offset 0x88
    const float* mPosRestRatio_s{};
    // static_param at offset 0x90
    const float* mJumpHeight_s{};
    // static_param at offset 0x98
    const float* mNearGrHeight_s{};
    Unk_71000b0800<Unk_71025b0578> _a0;
    u8 _a8[0xcc - 0xa8];
    bool _cc = false;
    bool _cd = false;
};
KSYS_CHECK_SIZE_NX150(BackFlip, 0xd0);

}  // namespace uking::action
