#pragma once

#include "Game/Actor/AI/aiEnemyDefaultReaction.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::ai {

class GuardianMiniReaction : public EnemyDefaultReaction {
    SEAD_RTTI_OVERRIDE(GuardianMiniReaction, EnemyDefaultReaction)
public:
    explicit GuardianMiniReaction(const InitArg& arg);
    ~GuardianMiniReaction() override;
    bool m36(int damage_type) override;
    void m39(ksys::act::ai::InlineParamPack* params) override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void m42(ksys::act::ai::InlineParamPack* params) override;

    void changeToChance();
    // 0x710041ee9c (placeholder name)
    void changeToDying();
    void m40(ksys::act::ai::InlineParamPack* params) override;
    void m35(act::DamageManagerBase* damage_mgr, int damage_type, bool x,
             ksys::act::ai::InlineParamPack* params) override;
    // 0x710041f990 / 0x71004201a4 (declared only; placeholder names): called by m35.
    bool sub_710041F990(bool from_player);
    // `unused` (w4) is never read; m35 leaves the register unset in the original.
    void sub_71004201A4(const sead::SafeString& name, s32 a, s32 b, s32 unused, s32 e);
protected:
    // static_param at offset 0x68
    sead::SafeString mRootNodeName_s{};
    // static_param at offset 0x78
    sead::SafeString mArm1NodeName_s{};
    // static_param at offset 0x88
    sead::SafeString mArm2NodeName_s{};
    // static_param at offset 0x98
    sead::SafeString mArm3NodeName_s{};
    // static_param at offset 0xa8
    const int* mASSlotRight_s{};
    // static_param at offset 0xb0
    const int* mASSlotLeft_s{};
    // static_param at offset 0xb8
    const int* mASSlotBack_s{};
    // static_param at offset 0xc0
    sead::SafeString mPreAttackASRight_s{};
    // static_param at offset 0xd0
    sead::SafeString mPreAttackASLeft_s{};
    // static_param at offset 0xe0
    const int* mJustGuardNumForBreak_s{};
    // static_param at offset 0xe8
    const bool* mIsChangeWeapon_s{};
    // aitree_variable at offset 0xf0
    int* mGuardianMiniChanceTimeState_a{};
    bool _f8;
    bool _f9;
    bool _fa;
    s32 _fc = 0;
    ksys::act::BaseProcLink _100;
};

}  // namespace uking::ai
