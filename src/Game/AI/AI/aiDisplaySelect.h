#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DisplaySelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DisplaySelect, ksys::act::ai::Ai)
public:
    explicit DisplaySelect(const InitArg& arg);
    ~DisplaySelect() override;
    bool isFailed() const override;
    bool isFinished() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void sub_7100361960(ksys::act::ai::InlineParamPack* params);

protected:
    // static_param at offset 0x38
    const float* mRadius_s{};
    // static_param at offset 0x40
    const bool* mIsCheckEveryFrame_s{};
};

}  // namespace uking::ai
