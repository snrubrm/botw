#pragma once

#include "Game/AI/AI/aiEnemyDefaultReaction.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::ai {

class GuardianMiniReaction : public EnemyDefaultReaction {
    SEAD_RTTI_OVERRIDE(GuardianMiniReaction, EnemyDefaultReaction)
public:
    explicit GuardianMiniReaction(const InitArg& arg);
    ~GuardianMiniReaction() override;
    void m39(ksys::act::ai::InlineParamPack* params) override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void m42(ksys::act::ai::InlineParamPack* params) override;

    void sub_7100420E7C();
    void m40(ksys::act::ai::InlineParamPack* params) override;
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
    u32 _fc = 0;
    ksys::act::BaseProcLink _100;
};

}  // namespace uking::ai
