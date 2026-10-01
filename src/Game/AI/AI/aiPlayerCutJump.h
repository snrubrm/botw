#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PlayerCutJump : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PlayerCutJump, ksys::act::ai::Ai)
public:
    explicit PlayerCutJump(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void loadParams_() override;

    bool isFinished() const override { return getCurrentChild()->isFinished(); }
    bool isFailed() const override { return getCurrentChild()->isFailed(); }
    bool isChangeable() const override { return getCurrentChild()->isChangeable(); }

protected:
};

}  // namespace uking::ai
