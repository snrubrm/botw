#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class BlownOff : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(BlownOff, ksys::act::ai::Ai)
public:
    explicit BlownOff(const InitArg& arg);
    bool isFinished() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    virtual void m34(ksys::act::ai::InlineParamPack* params);

    // 0x710032f364 (placeholder name): casts a ray from the actor's position (the center of the controller's body
    // when it has one) down to the DrownDepth below the water / ground reference height: true when it hits
    // something (or when the actor is not in contact with the ground / is above the body).
    bool sub_710032F364();

protected:
    // static_param at offset 0x38
    const float* mDrownDepth_s{};
    // static_param at offset 0x40
    const bool* mIsForceGetUp_s{};
    // static_param at offset 0x48
    const bool* mIsIceBreak_s{};
};

}  // namespace uking::ai
