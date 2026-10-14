#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AwarenessScale : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AwarenessScale, ksys::act::ai::Ai)
public:
    explicit AwarenessScale(const InitArg& arg);
    ~AwarenessScale() override;

    bool isFailed() const override;
    bool isFinished() const override;
    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mScale_s{};
    f32 _40;
    f32 _44;
    f32 _48;
    f32 _4c;
};

}  // namespace uking::ai
