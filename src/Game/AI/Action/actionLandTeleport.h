#pragma once

#include "Game/AI/Action/actionTeleportBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include <math/seadVector.h>
#include <limits>

namespace uking::action {

class LandTeleport : public TeleportBase {
    SEAD_RTTI_OVERRIDE(LandTeleport, TeleportBase)
public:
    explicit LandTeleport(const InitArg& arg);
    ~LandTeleport() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m40();
    virtual int m41();

    // static_param at offset 0x78
    const float* mDistXZ_s{};
    // static_param at offset 0x80
    const float* mDistY_s{};
    // static_param at offset 0x88
    const float* mSearchClosestPointRadius_s{};
    // static_param at offset 0x90
    const bool* mIsNormalizeAxisY_s{};
    sead::Vector3f _98 = sead::Vector3f::zero;
    sead::Vector3f _a4 = sead::Vector3f::zero;
    sead::Vector3f _b0{std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN(),
                      std::numeric_limits<f32>::quiet_NaN()};
};

KSYS_CHECK_SIZE_NX150(LandTeleport, 0xc0);

}  // namespace uking::action
