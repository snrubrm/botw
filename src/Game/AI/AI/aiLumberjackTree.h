#pragma once

#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LumberjackTree;

// Placeholder name (vtable address; inherits DamageCallback's RTTI). `_40` of LumberjackTree.
class Unk_7102403fe8 : public dmg::DamageCallback {
public:
    explicit Unk_7102403fe8(LumberjackTree* owner) : _28(owner) {}
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;

    LumberjackTree* _28;
};

class LumberjackTree : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LumberjackTree, ksys::act::ai::Ai)
public:
    explicit LumberjackTree(const InitArg& arg);
    ~LumberjackTree() override;

    bool hasPreDeleteCb() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    // 0x710048a190 (placeholder name): emits "Leaf", then drops the loot at the force-set drop position and
    // deletes the actor.
    void sub_710048A190();

protected:
    // FIXME: remove this
    u8 pad_0x38[0x8];
    Unk_7102403fe8 _40{this};
    u8 pad_0x70[0x250 - 0x70];
    // static_param at offset 0x250
    const float* mFallInterval_s{};
    // static_param at offset 0x258
    const float* mFellImpRate_s{};
    // static_param at offset 0x260
    const float* mFellRotRate_s{};
    // static_param at offset 0x268
    const float* mCutOffsetLower_s{};
    // static_param at offset 0x270
    const float* mCutOffsetUpper_s{};
    // static_param at offset 0x278
    const float* mAlphaLower_s{};
    // static_param at offset 0x280
    const float* mAlphaSpeed_s{};
    // map_unit_param at offset 0x288
    const float* mCutRate_m{};
    // map_unit_param at offset 0x290
    const float* mAngleY_m{};
    // map_unit_param at offset 0x298
    sead::SafeString mDropTable_m{};
    // aitree_variable at offset 0x2a8
    int* mLumberjackType_a{};
    // aitree_variable at offset 0x2b0
    sead::Vector3f* mForceSetDropPos_a{};
    // aitree_variable at offset 0x2b8
    sead::Vector3f* mMoveDirection_a{};
};

}  // namespace uking::ai
