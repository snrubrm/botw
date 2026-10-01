#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PrevSomeASSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PrevSomeASSelect, ksys::act::ai::Ai)
public:
    explicit PrevSomeASSelect(const InitArg& arg);
    ~PrevSomeASSelect() override;

    bool isFailed() const override { return getCurrentChild()->isFailed(); }
    bool isFinished() const override { return getCurrentChild()->isFinished(); }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mSeqBank_s{};
    // static_param at offset 0x40
    const int* mTargetBone_s{};
    // static_param at offset 0x48 ("ASName0".."ASName5")
    sead::SafeString mASName_s[6];
};

}  // namespace uking::ai
