#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class inWaterSelForkASPlay : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(inWaterSelForkASPlay, ksys::act::ai::Action)
public:
    explicit inWaterSelForkASPlay(const InitArg& arg);
    ~inWaterSelForkASPlay() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mEndState_s{};
    // static_param at offset 0x28
    const int* mChangeableTiming_s{};
    // static_param at offset 0x30
    const int* mSeqBank_s{};
    // static_param at offset 0x38
    const int* mTargetBone_s{};
    // static_param at offset 0x40
    const float* mFirstRandomRatio_s{};
    // static_param at offset 0x48
    const bool* mIsIgnoreSame_s{};
    // static_param at offset 0x50
    sead::SafeString mASName_s{};
    f32 _60 = 0.0f;
};
KSYS_CHECK_SIZE_NX150(inWaterSelForkASPlay, 0x68);

}  // namespace uking::action
