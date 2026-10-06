#pragma once

#include <prim/seadBitFlag.h>
#include <prim/seadEnum.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseEatCarriedItem : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(HorseEatCarriedItem, ksys::act::ai::Action)
public:
    explicit HorseEatCarriedItem(const InitArg& arg);
    ~HorseEatCarriedItem() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    SEAD_ENUM(Bit, _0, _1)

    void calc_() override;

    // static_param at offset 0x20
    const float* mThresholdForEat_s{};
    // static_param at offset 0x28
    const sead::Vector3f* mCarriedItemPosRTYOffset_s{};
    // static_param at offset 0x30
    const sead::Vector3f* mCarriedItemPosRTYWidth_s{};
    // static_param at offset 0x38
    const float* mDelayFrames_s{};
    // dynamic_param at offset 0x40
    ksys::act::BaseProcLink* mTargetActor_d{};
    sead::BitFlag8 _48;
    u8 _49[0x3];
    s32 _4c = 0;
    sead::SafeString _50{};

};
KSYS_CHECK_SIZE_NX150(HorseEatCarriedItem, 0x60);

}  // namespace uking::action
