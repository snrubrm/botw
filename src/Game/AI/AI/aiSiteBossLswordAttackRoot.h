#pragma once

#include <gsys/gsysModelAccessKey.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class SiteBossLswordAttackRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SiteBossLswordAttackRoot, ksys::act::ai::Ai)
public:
    explicit SiteBossLswordAttackRoot(const InitArg& arg);
    ~SiteBossLswordAttackRoot() override;

    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void sub_7100579E30(const sead::Vector3f& pos, bool a2);
    void sub_7100579FA4();
    void sub_710057A348(const sead::Vector3f& pos, bool a2);

protected:
    // 0x710057aeb8: "火炎渦" child; fails without a target actor
    void sub_710057AEB8(const sead::Vector3f& pos, const sead::Vector3f& dest_pos);
    // 0x710057ab3c: "火球投げ" child with the fire ball actor name; fails without a target actor
    void sub_710057AB3C(const sead::Vector3f& pos);
    // 0x710057b254: changes to the "横斬り" child and updates the attack weights (the used one is lowered by 22, the others rise)
    void sub_710057B254(const sead::Vector3f& pos);
    // 0x710057b120: changes to the "回転斬り" child and updates the attack weights (the used one is lowered by 22, the others rise)
    void sub_710057B120(const sead::Vector3f& pos);
    // 0x710057aff0: changes to the "縦斬り" child and updates the attack weights (the used one is lowered by 22, the others rise)
    void sub_710057AFF0(const sead::Vector3f& pos);
    // 0x710057a810: changes to the "待機" child
    void sub_710057A810(const sead::Vector3f& pos);
    // static_param at offset 0x38
    const int* mHighSlashRate_s{};
    // static_param at offset 0x40
    const int* mWhirlSlashRate_s{};
    // static_param at offset 0x48
    const int* mFireBallRate_s{};
    // static_param at offset 0x50
    const int* mCrossSlashRate_s{};
    // static_param at offset 0x58
    const int* mTornadoAttackRate_s{};
    // static_param at offset 0x60
    const float* mChemicalPlusHPRate_s{};
    // static_param at offset 0x68
    const float* mIsFarDist_s{};
    // static_param at offset 0x70
    const float* mPatternShiftFirstLifeRate_s{};
    // static_param at offset 0x78
    const float* mReturnWaitCount_s{};
    // static_param at offset 0x80
    const float* mForceApproachCount_s{};
    // dynamic_param at offset 0x88
    bool* mIsAttackPatternFixed_d{};
    // dynamic_param at offset 0x90
    bool* mIsCancelAttack_d{};
    bool _98 = false;
    bool _99 = false;
    bool _9a = false;
    u32 _9c = 0;
    s32 _a0;
    s32 _a4;
    s32 _a8;
    s32 _ac;
    s32 _b0;
    gsys::BoneAccessKeyEx _b8;
    ksys::Timer _f0{0, 0, 0};
    ksys::Timer _fc{0, 0, 0};
};
KSYS_CHECK_SIZE_NX150(SiteBossLswordAttackRoot, 0x108);

}  // namespace uking::ai
