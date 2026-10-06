#pragma once

#include <math/seadVector.h>
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LumberjackFallenTree;

// Placeholder names (vtable addresses; they inherit DamageCallback's RTTI). `_38` / `_68` of LumberjackFallenTree.
// vtable 0x7102403e48: call 0x7100485538, D0 0x7100487104.
class Unk_7102403e48 : public dmg::DamageCallback {
public:
    explicit Unk_7102403e48(LumberjackFallenTree* owner) : _28(owner) {}
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;

    LumberjackFallenTree* _28;
};

// vtable 0x7102403e80: call 0x710048554c, D0 0x710048714c.
class Unk_7102403e80 : public dmg::DamageCallback {
public:
    explicit Unk_7102403e80(LumberjackFallenTree* owner) : _28(owner) {}
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;

    LumberjackFallenTree* _28;
};

class LumberjackFallenTree : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LumberjackFallenTree, ksys::act::ai::Ai)
public:
    explicit LumberjackFallenTree(const InitArg& arg);
    ~LumberjackFallenTree() override;

    bool hasUpdateForPreDeleteCb() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    // 0x71004855dc (declared only; the CSV name agl::eft::Star::updateUBO is wrong): called by the damage callback
    // `_68` with the damage manager's position.
    void sub_71004855DC(const sead::Vector3f& position);

protected:
    Unk_7102403e48 _38{this};
    Unk_7102403e80 _68{this};
    // static_param at offset 0x98
    const float* mToLogAngVel_s{};
    // static_param at offset 0xa0
    const float* mMaxCheckAng_s{};
    // static_param at offset 0xa8
    const float* mCheckDis_s{};
    // static_param at offset 0xb0
    const float* mCheckHeightRate_s{};
    // static_param at offset 0xb8
    const float* mTerrorRegistAng_s{};
    // static_param at offset 0xc0
    const float* mTerrorUnregistTimelimit_s{};
    // static_param at offset 0xc8
    const float* mNoiseLevel_s{};
    // static_param at offset 0xd0
    const bool* mIsCheckHeight_s{};
    // static_param at offset 0xd8
    const sead::Vector3f* mTerrorOffsetPos4Falling_s{};
    // aitree_variable at offset 0xe0
    int* mLumberjackType_a{};
    // aitree_variable at offset 0xe8
    sead::Vector3f* mForceSetDropPos_a{};
    // aitree_variable at offset 0xf0
    sead::Vector3f* mMoveDirection_a{};
};

}  // namespace uking::ai
