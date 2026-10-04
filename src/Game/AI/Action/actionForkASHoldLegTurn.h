#pragma once

#include "Game/AI/aiUnk_710070E434.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkASHoldLegTurn : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkASHoldLegTurn, ksys::act::ai::Action)
public:
    explicit ForkASHoldLegTurn(const InitArg& arg);
    ~ForkASHoldLegTurn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x710013ee00 (declared only): the body of calc_ is out of line in the original.
    void sub_710013EE00();
    void calc_() override;

    // static_param at offset 0x20
    const float* mRotSpeed_s{};
    // static_param at offset 0x28
    const float* mStopSpeedRatio_s{};
    // static_param at offset 0x30
    const float* mStopRotSpeedRatio_s{};
    // static_param at offset 0x38
    const float* mTargetPosNoUpdateArea_s{};
    // static_param at offset 0x40
    const bool* mIsFixBoneWithGround_s{};
    // static_param at offset 0x48
    sead::SafeString mRotBaseBoneName_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
    Unk_710070e434 _60{mActor};
    sead::Vector3f _178;
};
KSYS_CHECK_SIZE_NX150(ForkASHoldLegTurn, 0x188);

}  // namespace uking::action
