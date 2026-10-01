#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/VFRValue.h"

namespace uking::action {

class ForkAerialAcrobatics : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkAerialAcrobatics, ksys::act::ai::Action)
public:
    explicit ForkAerialAcrobatics(const InitArg& arg);
    ~ForkAerialAcrobatics() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mSpeedKeepRatio_s{};
    // static_param at offset 0x28
    const float* mRotSpeedKeepRatio_s{};
    // static_param at offset 0x30
    const float* mMinGravityScale_s{};
    // static_param at offset 0x38
    const float* mGravityPer_s{};
    // static_param at offset 0x40
    const float* mRetGravityPer_s{};
    // static_param at offset 0x48
    const bool* mIsStopGravitySpeed_s{};
    ksys::VFRValue _50;
    f32 _5c = 0;
    bool _60 = false;
};

KSYS_CHECK_SIZE_NX150(ForkAerialAcrobatics, 0x68);

}  // namespace uking::action
