#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TrgTargetChangeToPlayerSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TrgTargetChangeToPlayerSelect, ksys::act::ai::Ai)
public:
    explicit TrgTargetChangeToPlayerSelect(const InitArg& arg);
    ~TrgTargetChangeToPlayerSelect() override;

    bool isFailed() const override { return getCurrentChild()->isFailed(); }
    bool isFinished() const override { return getCurrentChild()->isFinished(); }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x38
    bool* mIsTrgTargetChangeToPlayer_a{};
};

}  // namespace uking::ai
