#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

class ForkGanonBeastWeakPointCheck;

// Native tables share DamageCallback's RTTI and complete destructor slots.
class Unk_710238b078 : public dmg::DamageCallback {
public:
    explicit Unk_710238b078(ForkGanonBeastWeakPointCheck* owner) : mOwner(owner) {}
    void call(s32*, s32*, u32*, u32*, s32*, dmg::DamageCallbackInfo*) override;
    ForkGanonBeastWeakPointCheck* mOwner;
    ksys::phys::RigidBody* mBody = nullptr;
};
KSYS_CHECK_SIZE_NX150(Unk_710238b078, 0x38);

class Unk_710238b0b0 : public dmg::DamageCallback {
public:
    explicit Unk_710238b0b0(ForkGanonBeastWeakPointCheck* owner) : mOwner(owner) {}
    void call(s32*, s32*, u32*, u32*, s32*, dmg::DamageCallbackInfo*) override;
    ForkGanonBeastWeakPointCheck* mOwner;
    s32 mWeakPoint = 18;
};
KSYS_CHECK_SIZE_NX150(Unk_710238b0b0, 0x38);

class Unk_710238b040 : public dmg::DamageCallback {
public:
    void call(s32*, s32*, u32*, u32*, s32*, dmg::DamageCallbackInfo*) override;
};
KSYS_CHECK_SIZE_NX150(Unk_710238b040, 0x28);

class ForkGanonBeastWeakPointCheck : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkGanonBeastWeakPointCheck, ksys::act::ai::Action)
    friend class Unk_710238b078;
public:
    explicit ForkGanonBeastWeakPointCheck(const InitArg& arg);
    ~ForkGanonBeastWeakPointCheck() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mASSlot_s{};
    // static_param at offset 0x28
    const int* mLastWeakSlowEndSafeTime_s{};
    // static_param at offset 0x30
    const float* mLastWeakCounter_s{};
    // aitree_variable at offset 0x38
    int* mLastDamageWeakPointIdx_a{};
    // aitree_variable at offset 0x40
    bool* mIsWeakPointAppearMode_a{};
    // aitree_variable at offset 0x48
    void* mWeakPointActiveFlag_a{};
    // aitree_variable at offset 0x50
    void* mWeakPointAliveFlag_a{};
    // aitree_variable at offset 0x58
    void* mGanonBeastWeakPointXLinkHandle_a{};
    // aitree_variable at offset 0x60
    void* mWeakPointCounter_a{};

    // Members not recovered yet (class size from the factory).
    u8 _68[0x140 - 0x68];
    Unk_710238b078 mWeakPointDamageCallback{this};
    Unk_710238b0b0 mLastWeakPointDamageCallback{this};
    Unk_710238b040 mDamageCallback;
    Unk_71012419b4 _1d8;
    // Full 1556D4 updates the two independent countdowns using Timer::update.
    f32 _1f8 = 0.0f;
    f32 _1fc = 0.0f;
    bool _200 = false;
    bool _201 = false;
};
KSYS_CHECK_SIZE_NX150(ForkGanonBeastWeakPointCheck, 0x208);

}  // namespace uking::action
