#pragma once

#include "Game/AI/Action/actionSwimMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SwimMoveASHoldEvent : public SwimMoveBase {
    SEAD_RTTI_OVERRIDE(SwimMoveASHoldEvent, SwimMoveBase)
public:
    explicit SwimMoveASHoldEvent(const InitArg& arg);
    ~SwimMoveASHoldEvent() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    void m32(f32 a, f32 b, f32 c, f32 d, f32 e) override;

    // static_param at offset 0xe8
    const float* mPosReduceRatio_s{};
    // static_param at offset 0xf0
    sead::SafeString mASName_s{};
    f32 _100 = -10.0f;
};

}  // namespace uking::action
