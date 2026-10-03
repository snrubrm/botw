#pragma once

#include <prim/seadEnum.h>
#include <prim/seadBitFlag.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseEatAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(HorseEatAction, ksys::act::ai::Action)
public:
    explicit HorseEatAction(const InitArg& arg);
    ~HorseEatAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    SEAD_ENUM(Bit, _0, _1)

    void calc_() override;

    // static_param at offset 0x20
    const float* mTargetDirToStickX_s{};
    // static_param at offset 0x28
    const float* mTargetDistOffset_s{};
    // static_param at offset 0x30
    const float* mTargetDistToStickY_s{};
    // static_param at offset 0x38
    const float* mMaxStickXForEat_s{};
    // static_param at offset 0x40
    const float* mMaxStickYForEat_s{};
    // static_param at offset 0x48
    const float* mDelayFrames_s{};
    // dynamic_param at offset 0x50
    ksys::act::BaseProcLink* mTargetActor_d{};
    sead::BitFlag8 _58;
    f32 _5c = 0;
    sead::SafeString _60;
};

KSYS_CHECK_SIZE_NX150(HorseEatAction, 0x70);

}  // namespace uking::action
