#pragma once

#include <prim/seadSafeString.h>
#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace ksys::act {
class PhysicsUserTag;
}

namespace uking::ai {

class LumberjackTree;

// Placeholder name (vtable address; inherits DamageCallback's RTTI). `_40` of LumberjackTree.
class Unk_7102403fe8 : public dmg::DamageCallback {
public:
    explicit Unk_7102403fe8(LumberjackTree* owner) : _28(owner) {}
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, dmg::DamageCallbackInfo* a6) override;

    LumberjackTree* _28;
};

// Placeholder (the fourth argument of Unk_7102404020::m0; only the two words it reads).
struct Unk_7102404020_Arg7 {
    u8 _0[0x18];
    u32 _18;
    u32 _1c;
};

// Placeholder name (vtable 0x7102404020: a single virtual, no destructor; like SimpleWildlifeRoot's
// Unk_71023dcc38 with the pointer to itself at +0x18). `_70` of LumberjackTree.
class Unk_7102404020_Base {
public:
    virtual bool m0(const sead::Vector3f* pos, void* a2, void* a3, void* a4, void* a5, void* a6,
                    const Unk_7102404020_Arg7* a7, const ksys::act::PhysicsUserTag* tag) = 0;

    void* _8 = nullptr;
    void* _10 = nullptr;
    Unk_7102404020_Base* _18 = this;
    void* _20 = nullptr;
};

class Unk_7102404020 : public Unk_7102404020_Base {
public:
    // 0x71004873f0: true when the tagged actor passes the 0x71006e3ab0 check and `pos->y - _30` is
    // outside [_28, _2c]. Only `pos`, `a7` and `tag` are used.
    virtual bool m0(const sead::Vector3f* pos, void* a2, void* a3, void* a4, void* a5, void* a6,
                    const Unk_7102404020_Arg7* a7, const ksys::act::PhysicsUserTag* tag) override;

    f32 _28 = 9999.0f;
    f32 _2c = 9999.0f;
    f32 _30 = 0.0f;
};
KSYS_CHECK_SIZE_NX150(Unk_7102404020, 0x38);

// Placeholder name (vtable 0x7102404038; message 0x800001a, no payload). `_f8` of LumberjackTree.
class Unk_7102404038 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return nullptr; }
};

class LumberjackTree : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LumberjackTree, ksys::act::ai::Ai)
public:
    explicit LumberjackTree(const InitArg& arg);
    ~LumberjackTree() override;

    bool hasPreDeleteCb() override;
    void onPreDelete() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    // 0x710048a190 (placeholder name): emits "Leaf", then drops the loot at the force-set drop position and
    // deletes the actor.
    void sub_710048A190();

protected:
    void* _38 = nullptr;
    Unk_7102403fe8 _40{this};
    Unk_7102404020 _70;
    Unk_7102404060 _a8;
    Unk_7102404038 _f8{mActor, 0x800001a};
    Unk_7102450a08 _110;
    Unk_710237ecc0 _160{mActor};
    sead::FixedSafeString<0x40> _190;
    sead::FixedSafeString<0x40> _1e8;
    u8 _240 = 0xff;  // Original constructor sentinel; enter_ assigns tree kinds 0, 1 and 2.
    f32 _244 = 1.0f;
    u32 _248 = 0;
    bool _24c = false;
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

    sead::Vector3f _2c0;
    sead::Vector3f _2cc;
    u32 _2d8 = 0;
    u16 _2dc = 0;
    void* _2e0 = nullptr;  // sound handle (freed through 0x7100da2330 in D1)
    void* _2e8 = nullptr;  // phys::Constraint (destroyed in D1)
    u32 _2f0 = 0;
    u16 _2f4 = 0;
    u8 _2f6 = 0;
};
KSYS_CHECK_SIZE_NX150(LumberjackTree, 0x2f8);

}  // namespace uking::ai
