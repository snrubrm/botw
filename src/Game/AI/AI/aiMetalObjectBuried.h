#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MetalObjectBuried : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(MetalObjectBuried, ksys::act::ai::Ai)
public:
    explicit MetalObjectBuried(const InitArg& arg);
    ~MetalObjectBuried() override;
    bool handleMessage_(const ksys::Message* message) override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void changeToUnderground();
protected:
    // static_param at offset 0x38
    const float* mPullOutSpeed_s{};
    // static_param at offset 0x40
    const float* mCheckGroundRadiusScale_s{};
    // static_param at offset 0x48
    const bool* mIsIgnoreResistanceArea_s{};
    // static_param at offset 0x50
    const bool* mIsCheckGrabYPosFix_s{};
    // static_param at offset 0x58
    const bool* mIsCheckSelfY_s{};
    // map_unit_param at offset 0x60
    const bool* mIsInGround_m{};
    // map_unit_param at offset 0x68
    const bool* mEnableRevival_m{};
    bool _70{};
    bool _71{};
    bool _72{};
    f32 _74{};
    sead::Vector3f _78{0, 0, 0};
    sead::Vector3f _84{0, 0, 0};
};

}  // namespace uking::ai
