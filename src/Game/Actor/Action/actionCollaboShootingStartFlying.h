#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/World/worldShootingStarMgrEx.h"

namespace uking::action {

class CollaboShootingStartFlying : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(CollaboShootingStartFlying, ksys::act::ai::Action)
public:
    explicit CollaboShootingStartFlying(const InitArg& arg);
    ~CollaboShootingStartFlying() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    // 0x71000e1384 (placeholder name; same as ShootingStartFlying::sub_71002502E8): whether the actor is in front of
    // the camera and inside the centre of the screen.
    bool sub_71000E1384();

    // static_param at offset 0x20
    const float* mInitialVelocityMax_s{};
    // static_param at offset 0x28
    const float* mInitialVelocityMin_s{};
    // static_param at offset 0x30
    const float* mLookSuccessRate_s{};
    // aitree_variable at offset 0x38
    sead::SafeString* mCollaboShootingStarId_a{};
    ksys::world::ShootingStarAnchor::Identifier mIdentifier;
    Unk_71012419b4 _58;
    f32 _78 = 0;
    f32 _7c = 0;
    f32 _80 = 0;
    f32 _84 = 0;
};

}  // namespace uking::action
