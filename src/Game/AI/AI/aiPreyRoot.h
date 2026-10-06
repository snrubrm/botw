#pragma once

#include <limits>
#include <math/seadVector.h>
#include "Game/AI/aiUnk_710071edf8.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/System/VFRValue.h"

namespace uking::act {
class Enemy;
}

namespace uking::ai {

// Damage callbacks used by PreyRoot (vtables in PreyRoot's TU; they use DamageCallback's RTTI).
// Their `call` reads its last argument as an object of an unknown RTTI class and is not defined yet.
// vtable 0x7102410b48
class Unk_7102410b48 : public dmg::DamageCallback {
public:
    explicit Unk_7102410b48(ksys::act::Actor* actor) : mActor(actor) {}
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;

    ksys::act::Actor* mActor;
};

// vtable 0x7102410b80
class Unk_7102410b80 : public dmg::DamageCallback {
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;
};

// vtable 0x7102410bb8
class Unk_7102410bb8 : public dmg::DamageCallback {
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;
};

// vtable 0x7102410b10
class Unk_7102410b10 : public dmg::DamageCallback {
public:
    explicit Unk_7102410b10(ksys::act::Actor* actor) : mActor(actor) {}
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;

    ksys::act::Actor* mActor;
};

class PreyRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PreyRoot, ksys::act::ai::Ai)
public:
    explicit PreyRoot(const InitArg& arg);
    ~PreyRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

    virtual bool m34();
    virtual bool m35();
    virtual bool m36();
    virtual bool m37();
    virtual bool m38();
    virtual bool m39();
    virtual void m40();
    virtual void m41();
    virtual void m42();
    virtual void m43();
    virtual void m44();
    virtual void m45();
    virtual void m46();
    // The body of m47 is a call of sub_71005047A8 (the original m47 is `b 0x5047a8`).
    virtual void m47() { sub_71005047A8(); }
    // Unnamed in the binary (0x71005047a8); changes to the "通常行動" child with the actor position.
    void sub_71005047A8();
    // Unnamed in the binary (0x71005044c8): sub_7100504BF0(), then changes to the "水中行動" child with the
    // actor position.
    void sub_71005044C8();
    // Unnamed in the binary (0x7100504bf0): resets _1fc / _200 / _205.
    void sub_7100504BF0();
    // Unnamed in the binary (0x7100504a9c): sets / clears `mask` in the enemy's _e84 flags.
    void sub_7100504A9C(u32 mask, bool on);
    // Unnamed in the binary (0x7100504ebc): whether any bit of `mask` is set in the enemy's _e84 flags.
    bool sub_7100504EBC(u32 mask) const;

protected:
    void calc_() override;
    void sub_71005035A8();
    void sub_7100503864();
    void sub_7100503A78();
    // Unnamed in the binary (0x7100504070): m34() and the controller's _116 / _18c flags say it is in a
    // grounded-like state.
    bool sub_7100504070();
    // 0x7100504ed0 (lane1 s22): clears the disappear type and deletes the actor (same sequence as BirdEscape)
    void sub_7100504ED0();

    // static_param at offset 0x38
    const int* mAfterEscapeForceEndState_s{};
    // static_param at offset 0x40
    const float* mInWaterDepth_s{};
    // static_param at offset 0x48
    const float* mEscapeForceEndTime_s{};
    // static_param at offset 0x50
    const bool* mIsCheckFreeFall_s{};
    // static_param at offset 0x58
    const bool* mIsCheckStuckConsiderY_s{};
    // static_param at offset 0x60
    const bool* mIsUseWeakForcePushOutside_s{};
    // static_param at offset 0x68
    const bool* mIsEnableEscapeForceEndCheck_s{};
    // aitree_variable at offset 0x70
    int* mCreateDeadConditionType_a{};
    // aitree_variable at offset 0x78
    float* mFramesStuckOnTerrain_a{};
    // aitree_variable at offset 0x80
    bool* mIsStuckOnTerrain_a{};
    // aitree_variable at offset 0x88
    bool* mIsChangeableStateFreeFall_a{};
    // aitree_variable at offset 0x90
    bool* mIsUseTerritory_a{};
    Unk_7102410b48 _98{mActor};
    Unk_7102410b80 _c8;
    Unk_7102410bb8 _f0;
    Unk_7102410b10 _118{mActor};
    Unk_71024507c8 _148{0x1800004};
    act::Enemy* _188{};
    sead::Vector3f _190 = {0, 0, 0};
    sead::Vector3f _19c = {0, 0, 0};
    ksys::VFRValue _1a8;
    ksys::Timer _1b4{0, 0, 0};
    Unk_710071edf8 _1c0{mActor};
    ksys::Timer _1f0{0, 0, 0};
    f32 _1fc = std::numeric_limits<f32>::quiet_NaN();
    f32 _200 = 0;
    bool _204 = false;
    bool _205 = false;
};
KSYS_CHECK_SIZE_NX150(PreyRoot, 0x208);

}  // namespace uking::ai
