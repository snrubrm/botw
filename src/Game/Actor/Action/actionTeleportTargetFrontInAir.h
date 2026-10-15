#pragma once

#include "Game/Actor/Action/actionTeleportBase.h"
#include <math/seadVector.h>
#include "KingSystem/System/Timer.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class TeleportTargetFrontInAir : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(TeleportTargetFrontInAir, ksys::act::ai::Action)
public:
    explicit TeleportTargetFrontInAir(const InitArg& arg);
    ~TeleportTargetFrontInAir() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // 0x7100296360 (placeholder name): turns the character controller towards the target position.
    void sub_7100296360();
    bool sub_7100296134(sead::Vector3f* out);

    // map_unit_param at offset 0x20
    const float* mTerritoryArea_m{};
    // static_param at offset 0x28
    const float* mDistMin_s{};
    // static_param at offset 0x30
    const float* mDistMax_s{};
    // static_param at offset 0x38
    const float* mFrontAngle_s{};
    // static_param at offset 0x40
    const float* mHeightOffset_s{};
    // static_param at offset 0x48
    const float* mTerritoryArea_s{};
    TeleportBase::SavedState _50;
    int _5c = 0;
    sead::Vector3f _60{0, 0, 0};
    ksys::Timer _6c;
};

}  // namespace uking::action
