#pragma once

#include <limits>
#include <math/seadVector.h>
#include "Game/AI/aiUnk_710071edf8.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actAiAi.h"
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

    virtual bool m34();
    virtual bool m35();
    virtual bool m36();
    virtual bool m37();
    virtual bool m38();

protected:
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
    sead::Vector3f _1b4 = {0, 0, 0};
    Unk_710071edf8 _1c0{mActor};
    sead::Vector3f _1f0 = {0, 0, 0};
    f32 _1fc = std::numeric_limits<f32>::quiet_NaN();
    u32 _200 = 0;
    bool _204 = false;
    bool _205 = false;
};
KSYS_CHECK_SIZE_NX150(PreyRoot, 0x208);

}  // namespace uking::ai
