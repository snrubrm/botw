#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WillBallAttackLevelSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WillBallAttackLevelSelect, ksys::act::ai::Ai)
public:
    explicit WillBallAttackLevelSelect(const InitArg& arg);
    ~WillBallAttackLevelSelect() override;

    bool isFailed() const override { return getCurrentChild()->isFailed(); }
    bool isFinished() const override { return getCurrentChild()->isFinished(); }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual bool m34() const { return getCurrentChild()->isChangeable(); }

protected:
    // dynamic_param at offset 0x38
    int* mLevel_d{};
};

}  // namespace uking::ai
