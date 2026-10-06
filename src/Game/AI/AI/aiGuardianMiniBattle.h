#pragma once

#include "Game/AI/AI/aiEnemyBattle.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianMiniBattle : public EnemyBattle {
    SEAD_RTTI_OVERRIDE(GuardianMiniBattle, EnemyBattle)
public:
    explicit GuardianMiniBattle(const InitArg& arg);
    ~GuardianMiniBattle() override;
    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

    virtual void m44(ksys::act::ai::InlineParamPack* params);
    virtual bool m45();

    void sub_7100413A38();
    bool sub_7100415140(s32 idx);
    s32 sub_7100415EAC();
    // 0x7100415258 (declaration only, 1136 B; placeholder name): sets up the arm bones of the rolling attack
    // for the weapon pair (a, b) from the static node names.
    void sub_7100415258(s32 a, s32 b, s32 c, s32 d);
    void m37() override;
    void m43(ksys::act::ai::InlineParamPack* params) override;
    bool m40() override;
    void changeToMoveTurning();

protected:
    // static_param at offset 0x90
    sead::SafeString mRootNodeName_s{};
    // static_param at offset 0xa0
    sead::SafeString mArm1NodeName_s{};
    // static_param at offset 0xb0
    sead::SafeString mArm2NodeName_s{};
    // static_param at offset 0xc0
    sead::SafeString mArm3NodeName_s{};
    // static_param at offset 0xd0
    const int* mASSlotRight_s{};
    // static_param at offset 0xd8
    const int* mASSlotLeft_s{};
    // static_param at offset 0xe0
    const int* mASSlotBack_s{};
    // static_param at offset 0xe8
    const int* mRollingInterval_s{};
    // static_param at offset 0xf0
    const float* mBaseDist_s{};
    // static_param at offset 0xf8
    const float* mFarDist_s{};
    // static_param at offset 0x100
    const bool* mIsIgnoreArmCondition_s{};
    // static_param at offset 0x108
    const int* mTurnMoveTime_s{};
    // static_param at offset 0x110
    const int* mTurnMovePer_s{};
    // static_param at offset 0x118
    const float* mTurnMoveStartDist_s{};
    // static_param at offset 0x120
    const int* mCounterStartDamageCount_s{};
    // static_param at offset 0x128
    const int* mCounterStartTime_s{};
    // static_param at offset 0x130
    const bool* mCheckOnNoNavMesh_s{};
    // aitree_variable at offset 0x138
    int* mDamagedCount_a{};
    bool _140 = false;
    bool _141 = false;
    s32 _144 = 0;
    Unk_7102450738 _148;
    ksys::Timer _188{0, 0};
    ksys::Timer _194{0, 0};
    ksys::Timer _1a0{0, 0};
    ksys::Timer _1ac{0, 0};
};
KSYS_CHECK_SIZE_NX150(GuardianMiniBattle, 0x1b8);

}  // namespace uking::ai
