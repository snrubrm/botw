#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PlayerDead : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PlayerDead, ksys::act::ai::Ai)
public:
    explicit PlayerDead(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void calc_() override;
    void loadParams_() override;

    bool isFinished() const override;
    bool isChangeable() const override;

protected:
    // static_param at offset 0x38
    const int* mRumbleType_s{};
    // static_param at offset 0x40
    const float* mRumblePower_s{};
};

}  // namespace uking::ai
