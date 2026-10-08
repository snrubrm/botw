#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class LandHumEnemyThrowWeapon : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LandHumEnemyThrowWeapon, ksys::act::ai::Ai)
public:
    explicit LandHumEnemyThrowWeapon(const InitArg& arg);
    ~LandHumEnemyThrowWeapon() override;
    bool isChangeable() const override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void changeToThrowWeapon();
    // 0x710046c574 (placeholder name): drops the weapon in slot WeaponIdx, then changes child "怒り".
    // 0x710046c380 (placeholder name): the weapon in slot WeaponIdx is gone, not in the calc state,
    // or held by the player.
    bool sub_710046C380();
    // 0x710046c6e0 (placeholder name): the weapon in slot WeaponIdx is still being thrown / handled
    // (m211, held by someone other than the player, `_d90` busy or `_68f`), else whether the wait
    // timer `_58` has run out.
    bool sub_710046C6E0();
    void sub_710046C574();
    // 0x710046cc20 (placeholder name; declared only)
    bool sub_710046CC20();

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const float* mThrowWeaponNearDist_s{};
    // static_param at offset 0x48
    const int* mWaitTimeMax_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
    ksys::Timer _58{0, 0};
    bool _64{};
};

}  // namespace uking::ai
