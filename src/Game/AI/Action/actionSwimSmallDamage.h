#pragma once

#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "Game/AI/Action/actionSmallDamage.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SwimSmallDamage : public SmallDamage {
    SEAD_RTTI_OVERRIDE(SwimSmallDamage, SmallDamage)
public:
    explicit SwimSmallDamage(const InitArg& arg);
    ~SwimSmallDamage() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x710028be2c (declared only): out of line in the original.
    void sub_710028BE2C(bool a);
    // static_param at offset 0x90
    const float* mInWaterDepth_s{};
    // static_param at offset 0x98
    const float* mFloatDepth_s{};
    // static_param at offset 0xa0
    const float* mFloatRadius_s{};
    // static_param at offset 0xa8
    sead::SafeString mASName_s{};
    ksys::act::CCAccessor _b8;
    void m38() override;
};

}  // namespace uking::action
