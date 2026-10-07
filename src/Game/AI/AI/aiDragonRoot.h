#pragma once

#include <container/seadBuffer.h>
#include <prim/seadBitFlag.h>
#include "Game/AI/AI/aiDragonRootBase.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::act { class Dragon; }

namespace uking::ai {

// vtable 0x71023e3a40: damage callback (functions in the DragonRoot TU); placeholder name.
class Unk_71023e3a40 : public dmg::DamageCallback {
    SEAD_RTTI_OVERRIDE(Unk_71023e3a40, dmg::DamageCallback)
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, dmg::DamageCallbackInfo* a6) override;
};

class DragonRoot : public DragonRootBase {
    SEAD_RTTI_OVERRIDE(DragonRoot, DragonRootBase)
public:
    explicit DragonRoot(const InitArg& arg);
    ~DragonRoot() override;
    bool handleMessage_(const ksys::Message* message) override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool reenter_(ksys::act::ai::ActionBase* other, bool x) override;

    // 0x710036f80c (placeholder name): enables the attack sensor with the BodyHit parameters and the attack bodies
    // of the actor's physics (`sub_71007A2B64` on those that are in / entering the world on the enemy attack layer).
    void sub_710036F80C();

    f32 m34() override;
    void m37() override;
    void m38() override;
    virtual void m40(f32 a1);
    virtual void m41();
    virtual void m42();
    virtual void m43();
    virtual void m44(const sead::Vector3f& pos);
    virtual void m45(ksys::act::Actor* actor);
    // Original drop helper at 0x7100370740; body remains declared only.
    void spawnDrop(act::Dragon* dragon, ksys::act::Actor* actor,
                   const sead::Vector3f& pos, const sead::Vector3f& velocity);
    virtual bool m46();
    virtual bool m47();

    // 0x20-byte element of _238 (allocated in init_ with ChemicalBulletNum entries).
    struct Unk1 {
        ksys::act::BaseProcHandle _0;
        ksys::act::BaseProcLink _10;
    };

    // Owner of the Unk1 array: the destructor frees it after _250 is destroyed, so the buffer is
    // freed by a member destructor rather than by ~DragonRoot's body. Placeholder.
    struct Unk2 {
        ~Unk2() { _0.freeBuffer(); }
        // 0x710036b89c (placeholder name): gives every ready entry's actor to its link and wakes it (DragonIceRoot::m42,
        // DragonRoot::m42).
        void sub_710036B89C();
        sead::Buffer<Unk1> _0;
    };

protected:
    Unk_71023e3a40 _98;
    // static_param at offset 0xc0
    const int* mChemicalBulletRate_s{};
    // static_param at offset 0xc8
    const int* mChemicalBulletNum_s{};
    // static_param at offset 0xd0
    const int* mUpdraftInterval_s{};
    // static_param at offset 0xd8
    const int* mReturnTime_s{};
    // static_param at offset 0xe0
    const int* mBodyHitDamage_s{};
    // static_param at offset 0xe8
    const int* mBodyHitPower_s{};
    // static_param at offset 0xf0
    const int* mBodyHitImpact_s{};
    // static_param at offset 0xf8
    const int* mBodyHitShieldDamage_s{};
    // static_param at offset 0x100
    const float* mOnRailDistance_s{};
    // static_param at offset 0x108
    const float* mFarDistance_s{};
    // static_param at offset 0x110
    const float* mSpeed_s{};
    // static_param at offset 0x118
    const float* mChemicalBulletArea_s{};
    // static_param at offset 0x120
    const float* mChemicalWindArea_s{};
    // static_param at offset 0x128
    const float* mChemicalWindPower_s{};
    // static_param at offset 0x130
    const float* mChemicalWindLimitHeight_s{};
    // static_param at offset 0x138
    const float* mUpdraftPower_s{};
    // static_param at offset 0x140
    const float* mUpdraftTime_s{};
    // static_param at offset 0x148
    const float* mUpdraftBoost_s{};
    // static_param at offset 0x150
    const float* mInitBackRailDistance_s{};
    // static_param at offset 0x158
    const bool* mIsEmitChemical_s{};
    // static_param at offset 0x160
    sead::SafeString mCommonTableName_s{};
    // static_param at offset 0x170
    sead::SafeString mTsunoTableName_s{};
    // static_param at offset 0x180
    sead::SafeString mTsumeTableName_s{};
    // static_param at offset 0x190
    sead::SafeString mKibaTableName_s{};
    // static_param at offset 0x1a0
    sead::SafeString mChemicalBulletActor_s{};
    // static_param at offset 0x1b0
    sead::SafeString mDefaultMaterialAnmName_s{};
    // static_param at offset 0x1c0
    sead::SafeString mHornAnmName_s{};
    // aitree_variable at offset 0x1d0
    sead::SafeString* mCreateRailName_a{};
    s32 _1d8 = 0;
    f32 _1dc = 0;
    f32 _1e0 = 0;
    sead::Vector3f _1e4;
    Unk_71023b0898 _1f0{mActor, 0x8000083};
    f32 _230 = 0;
    Unk2 _238;
    f32 _248 = 0;
    sead::BitFlag16 _24c;
    ksys::act::BaseProcHandle _250;
};
KSYS_CHECK_SIZE_NX150(DragonRoot, 0x260);

}  // namespace uking::ai
