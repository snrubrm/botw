#pragma once

#include "Game/AI/AI/aiEnemyRoot.h"
#include "Game/AI/aiUnk_710070F974.h"
#include "Game/AI/aiUnk_71025ba778.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

// Placeholder name (vtable address 0x7102406048; inherits DamageCallback's RTTI; `call` 0x710049b218, D0 0x710049b3f4):
// one of the damage callbacks embedded in LynelRoot (offset not recovered yet).
class Unk_7102406048 : public dmg::DamageCallback {
    SEAD_RTTI_OVERRIDE(Unk_7102406048, dmg::DamageCallback)
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, dmg::DamageCallbackInfo* a6) override;
};

class LynelRoot : public EnemyRoot {
    SEAD_RTTI_OVERRIDE(LynelRoot, EnemyRoot)
public:
    explicit LynelRoot(const InitArg& arg);
    ~LynelRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void m37() override;

protected:
    // static_param at offset 0x1d8
    const int* mBowIdx_s{};
    // static_param at offset 0x1e0
    const float* mBoneStandAddRatio_s{};
    // static_param at offset 0x1e8
    sead::SafeString mRoarFlameActorName_s{};
    // static_param at offset 0x1f8
    sead::SafeString mRoarFlamePartsKey_s{};
    // static_param at offset 0x208
    sead::SafeString mBreathActorName_s{};
    // static_param at offset 0x218
    sead::SafeString mBreathPartsKey0_s{};
    // static_param at offset 0x228
    sead::SafeString mBreathPartsKey1_s{};
    // static_param at offset 0x238
    sead::SafeString mBreathPartsKey2_s{};
    // static_param at offset 0x248
    sead::SafeString mStandBoneName_s{};
    // aitree_variable at offset 0x258
    int* mLynelAIFlags_a{};
    // aitree_variable at offset 0x260
    int* mLynelAreaAlarmPoint_a{};
    // aitree_variable at offset 0x268
    void* mLynelBodyControlUnit_a{};
    // aitree_variable at offset 0x270
    void* mLynelMoveParam_a{};
    Unk_71025c89e8 _278;
    Unk_71025ba778 _2c8;
    Unk_7102406048 _478;
    void* _4a0;  // not set by the constructor
};
KSYS_CHECK_SIZE_NX150(LynelRoot, 0x4a8);

}  // namespace uking::ai
