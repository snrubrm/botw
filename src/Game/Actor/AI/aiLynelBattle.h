#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LynelBattle : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LynelBattle, ksys::act::ai::Ai)
public:
    explicit LynelBattle(const InitArg& arg);
    ~LynelBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    // 0x710048d8a0 (placeholder name)
    void changeToMeleeBattle();
    // 0x710048e13c / 0x710048e278 / 0x710048e3d8 / 0x710048e538 / 0x710048e658 (placeholder names): set the attack
    // state bits of `mLynelAIFlags_a`, update the attack history and start the attack child.
    void changeToThroughAttack();
    void changeToChargeAttack(bool skip_prepare);
    void changeToSixLegAttack(bool skip_prepare);
    void changeToBreath();
    void changeToRoarAttack();
    // 0x710048eabc (placeholder name): picks the six leg attack or the charge attack with HornAttackRate, adjusted
    // by the attack history `_e0`.
    void changeToChargeOrSixLegAttack(bool skip_prepare);
    virtual void m34(bool skip_prepare);

protected:
    // 0x710048d794 / 0x710048deec / 0x710048e778 / 0x710048e8bc / 0x710048e9ec (placeholder names)
    bool sub_710048D794();
    bool sub_710048DEEC();
    bool sub_710048E778();
    bool sub_710048E8BC();
    bool sub_710048E9EC();

    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const int* mCloseBattleRepeatMax_s{};
    // static_param at offset 0x48
    const int* mThroughAttackRepeatNum_s{};
    // static_param at offset 0x50
    const float* mCloseBattleStartDist_s{};
    // static_param at offset 0x58
    const float* mCloseBattleStartAngle_s{};
    // static_param at offset 0x60
    const float* mHornAttackRate_s{};
    // static_param at offset 0x68
    const float* mRoarRate_s{};
    // static_param at offset 0x70
    const float* mBreathStartLifeRate_s{};
    // static_param at offset 0x78
    const float* mRoarStartLifeRate_s{};
    // static_param at offset 0x80
    const float* mBattleEndDist_s{};
    // static_param at offset 0x88
    const float* mSkipBreathRoarRate_s{};
    // static_param at offset 0x90
    sead::SafeString mRoarFlamePartsKey_s{};
    // static_param at offset 0xa0
    sead::SafeString mBreathPartsKey0_s{};
    // static_param at offset 0xb0
    sead::SafeString mBreathPartsKey1_s{};
    // static_param at offset 0xc0
    sead::SafeString mBreathPartsKey2_s{};
    // aitree_variable at offset 0xd0
    int* mLynelAIFlags_a{};
    int _d8{};
    int _dc{};
    s32 _e0{};
    s32 _e4{};
};

}  // namespace uking::ai
