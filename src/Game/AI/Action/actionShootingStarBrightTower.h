#pragma once

#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

class ShootingStarBrightTower : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ShootingStarBrightTower, ksys::act::ai::Action)
public:
    explicit ShootingStarBrightTower(const InitArg& arg);
    ~ShootingStarBrightTower() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // 0x710024f634 (CSV name shootingStarDropStuff; declared only): called from calc_ with the landing position.
    void shootingStarDropStuff(const sead::Vector3f& pos);

    // static_param at offset 0x20
    const float* mDisappearDistance_s{};
    // dynamic_param at offset 0x28
    sead::Vector3f* mHitGroundAngle_d{};
    Unk_71012419b4 _30;
    ksys::act::BaseProcHandle _50;
    sead::Vector3f _60 = sead::Vector3f::zero;
    sead::Matrix34f _6c = sead::Matrix34f::ident;
    sead::Vector3f _9c = sead::Vector3f::zero;
    f32 _a8 = 50.0f;
    f32 _ac = 0;  // timer: Timer::update(&_ac, 1)
};

}  // namespace uking::action
