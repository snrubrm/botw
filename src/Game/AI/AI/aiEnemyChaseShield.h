#pragma once

#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyChaseShield : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyChaseShield, ksys::act::ai::Ai)
public:
    explicit EnemyChaseShield(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;
    // 0x710038347c (placeholder name)
    void sub_710038347C();
    // 0x7100384290 (placeholder name)
    void sub_7100384290();
    // 0x71003840f4 (placeholder name)
    void sub_71003840F4();

protected:
    // dynamic_param at offset 0x38
    ksys::act::BaseProcLink* mTargetWeapon_d{};
    // static_param at offset 0x40
    const int* mEquipItemSearchIdx_s{};
    // static_param at offset 0x48
    const float* mTurnAng_s{};
    // static_param at offset 0x50
    const float* mShieldReachDist_s{};
    uking::act::Enemy::Unk_12d0* _58{};
};

}  // namespace uking::ai
