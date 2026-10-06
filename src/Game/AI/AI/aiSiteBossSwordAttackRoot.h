#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossSwordAttackRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SiteBossSwordAttackRoot, ksys::act::ai::Ai)
public:
    explicit SiteBossSwordAttackRoot(const InitArg& arg);
    ~SiteBossSwordAttackRoot() override;

    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x7100596400: the SiteBoss has both flags 6 set, _108 bit 2 is set and the boss's _1548 has run out
    bool sub_7100596400();
    // 0x7100595808: close attack: clears _108 bits 0x260; changes to the explicit "近接攻撃" / 2 / 3 child for `attack` 0 / 1 / 2 and then (always) to the one chosen by the HP rates
    void sub_7100595808(const sead::Vector3f& pos, s32 attack);
    // 0x7100595768: enter_ tail: the target position (the boss target when it is the player, else the player position), _108 |= 3, then sub_7100596A4C(pos, true)
    void sub_7100595768();
    // 0x7100596de4: SiteBoss flags 0x80 -> 0x800 and _1558 bit 0x40000 cleared, then the "落雷攻撃前移動" child
    void sub_7100596DE4(const sead::Vector3f& pos);
    // 0x7100596b48: SiteBoss flags 0x80 -> 0x800, _108 |= 1, then changes to the "落雷攻撃" child
    void sub_7100596B48(const sead::Vector3f& pos);
    // 0x7100596268: sets SiteBoss flag 0x80, then changes to the "待機" child
    void sub_7100596268(const sead::Vector3f& pos);
    // 0x71005955d4: sets SiteBoss flag 0x80, updates _108 / _10c, then changes to the "遠距離攻撃" child
    void sub_71005955D4(const sead::Vector3f& pos);
    // 0x7100596fa4: sets flag 0x20 of _108, then changes to the "退避" child
    void sub_7100596FA4(const sead::Vector3f& pos);
    // 0x7100596a4c: changes to the "盾突き" child
    void sub_7100596A4C(const sead::Vector3f& pos, bool attack_pattern_fixed);
    // static_param at offset 0x38
    const int* mCloseAttackRate_s{};
    // static_param at offset 0x40
    const int* mChemicalPlusRate_s{};
    // static_param at offset 0x48
    const int* mThrowAttackPower_s{};
    // static_param at offset 0x50
    const int* mAddAttackPower_s{};
    // static_param at offset 0x58
    const int* mThrowMinDamage_s{};
    // static_param at offset 0x60
    const int* mThrowRate_s{};
    // static_param at offset 0x68
    const int* mPillarMax_s{};
    // static_param at offset 0x70
    const int* mElectricCounterMax_s{};
    // static_param at offset 0x78
    const float* mChemicalPlusHPRate_s{};
    // static_param at offset 0x80
    const float* mShieldRepairTime_s{};
    // static_param at offset 0x88
    const float* mFirstAttackHPRate_s{};
    // static_param at offset 0x90
    const float* mSecondAttackHPRate_s{};
    // static_param at offset 0x98
    const float* mBeamAttackHPRate_s{};
    // static_param at offset 0xa0
    const float* mElectricBallScaleTime_s{};
    // static_param at offset 0xa8
    const float* mElectricBallScale_s{};
    // static_param at offset 0xb0
    const float* mElectricBallRange_s{};
    // static_param at offset 0xb8
    const float* mThrowDist_s{};
    // static_param at offset 0xc0
    sead::SafeString mDemoName_s{};
    // static_param at offset 0xd0
    sead::SafeString mEntryPointName_s{};
    // static_param at offset 0xe0
    sead::SafeString mThrowActorName_s{};
    // dynamic_param at offset 0xf0
    bool* mIsCancelAttack_d{};
    u32 _f8 = 0;
    sead::Vector3f _fc = sead::Vector3f::zero;
    u16 _108 = 0;
    u32 _10c = 0;
};
KSYS_CHECK_SIZE_NX150(SiteBossSwordAttackRoot, 0x110);

}  // namespace uking::ai
