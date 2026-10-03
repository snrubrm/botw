#pragma once

#include "Game/AI/Action/actionActionWithAS.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::act {
class Enemy;
}

namespace uking::action {

class ThrowWeapon : public ActionWithAS {
    SEAD_RTTI_OVERRIDE(ThrowWeapon, ActionWithAS)
public:
    explicit ThrowWeapon(const InitArg& arg);
    ~ThrowWeapon() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32(sead::Vector3f* pos, uking::act::Enemy* enemy, int weapon_idx);
    virtual void m33();

    // static_param at offset 0x30
    const int* mWeaponIdx_s{};
    // static_param at offset 0x38
    const float* mSpeedMin_s{};
    // static_param at offset 0x40
    const float* mSpeedMax_s{};
    // static_param at offset 0x48
    const float* mThrowAng_s{};
    // static_param at offset 0x50
    const float* mThrowBoomerangAng_s{};
    // static_param at offset 0x58
    const float* mThrowBoomerangSpeedMax_s{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
    // static_param at offset 0x68
    const bool* mIsForceDead_s{};

    sead::Vector3f _70;
    u8 _7c[4];
};

}  // namespace uking::action
