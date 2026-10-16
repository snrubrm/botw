#pragma once

#include "Game/Actor/actWeapon.h"

#include "Game/Actor/Action/actionEquipedAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EquipedDefaultWindWeapon : public EquipedAction {
    SEAD_RTTI_OVERRIDE(EquipedDefaultWindWeapon, EquipedAction)
public:
    explicit EquipedDefaultWindWeapon(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m36(bool x);
    virtual void m37();
    // 0x710010ecc0 / 0x710010ee64 (CSV names): the wind speed (per second) and flying distance, the Large
    // values scaled by the attack count rate when the weapon's attack flags have bit 1 or 2.
    f32 getWindSpeedRate();
    // inline-only in the original; name is a guess. Evidence: the same "large wind" test (the weapon's attack
    // flags, as in Arrow::sub_710046A9EC, with bit 1 or 2) is inlined twice into m36 and into
    // getWindSpeedRate / getWindFlyingDist.
    bool isLargeWind() const {
        auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
        if (!weapon)
            return false;
        u32 flags;
        if ((weapon->_af8._0 | 1) == 7)
            flags = weapon->_af8._4;
        else if (weapon->_d08)
            flags = weapon->_cf4;
        else
            flags = weapon->_c20._4;
        return flags & 6;
    }
    f32 getWindFlyingDist();
    // 0x710010f4b4 (CSV name): the attack position (Weapon::getAttackPosMaybe for request type 9, else the
    // actor position).
    void getAttackPosMaybe(sead::Vector3f* pos);
    // 0x710010f2d4 (CSV getAttackPosMaybe_0): the attack direction (from the attack position to the request
    // target for request type 9, else the holder's forward axis).
    void getAttackDirMaybe(sead::Vector3f* dir);

    sead::Heap* _40{};
    // static_param at offset 0x48
    const float* mWindRadius_s{};
    // static_param at offset 0x50
    const float* mWindRadiusLarge_s{};
    // static_param at offset 0x58
    const float* mWindSpeed_s{};
    // static_param at offset 0x60
    const float* mWindSpeedLarge_s{};
    // static_param at offset 0x68
    const float* mWindSpeedRate1_s{};
    // static_param at offset 0x70
    const float* mWindSpeedRate2_s{};
    // static_param at offset 0x78
    const float* mWindSpeedRate3_s{};
    // static_param at offset 0x80
    const float* mWindLength_s{};
    // static_param at offset 0x88
    const float* mCapsuleMaxSpeed_s{};
    // static_param at offset 0x90
    const float* mWindReduceRate_s{};
    // static_param at offset 0x98
    const float* mWindReduceRateLarge_s{};
    // static_param at offset 0xa0
    const float* mWindFlyingDist_s{};
    // static_param at offset 0xa8
    const float* mWindFlyingDistLarge_s{};
    // static_param at offset 0xb0
    const float* mWindFlyingDistRate1_s{};
    // static_param at offset 0xb8
    const float* mWindFlyingDistRate2_s{};
    // static_param at offset 0xc0
    const float* mWindFlyingDistRate3_s{};
};
KSYS_CHECK_SIZE_NX150(EquipedDefaultWindWeapon, 0xc8);

}  // namespace uking::action
