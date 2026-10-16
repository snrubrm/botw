#pragma once

#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "Game/Actor/Damage/dmgDamageCallback.h"

namespace ksys::phys {
class ContactPointInfo;
}

namespace uking::act {

class Guardian;
class GuardianComponent;

// Declaration-only prefix of the component's heap bind interface. Whole 3BBB4 / 40750
// identify its independent RTTI root at 25AF258. The full 13-slot object table at
// 235B408 was read; slots after the destructor are not declared here because their
// parameter domains remain incomplete. Its destructor is the key function (D0 3C2E0).
class GuardianComponentBind {
    SEAD_RTTI_BASE(GuardianComponentBind)
public:
    virtual ~GuardianComponentBind();
    // Slots 0x20-0x60 (vtable 0x710235b390; null entries are pure). Placeholder names; m7 is called by
    // GuardianComponent::preDelete2_, m10 by initMaybe, m13 by updateMtxFromPhysics.
    virtual bool m6() = 0;
    virtual void m7(const ksys::act::BaseProc::PreDeleteArg& arg) = 0;
    virtual void m8() = 0;
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual void m13() = 0;
    virtual void m14();

    /* 0x08 */ GuardianComponent* _8;
};
KSYS_CHECK_SIZE_NX150(GuardianComponentBind, 0x10);

// Heap subtype from full prepareInit_ 3C41C: allocates 0x38 bytes, installs 235B408,
// and writes its owner and scalar/vector prefix. Full 40750 / 4081C identify Derive
// RTTI 25AF248 (guard 25AF250, RTTI vtable 235AC28). D1 / D0 3C2DC / 3C2E4 are
// empty/delete. Whole GuardianBeamAttack 40EF30 and mutable scalar consumer 40EFDC
// use _30 after checking this RTTI. Remaining virtual slots stay unmodeled.
class Unk_710235b408 : public GuardianComponentBind {
    SEAD_RTTI_OVERRIDE(Unk_710235b408, GuardianComponentBind)
public:
    ~Unk_710235b408() override;
    bool m6() override;
    void m7(const ksys::act::BaseProc::PreDeleteArg& arg) override;
    void m8() override;
    void m9() override;
    void m13() override;

    /* 0x10 */ u8 _10[0x30 - 0x10];
    /* 0x30 */ f32 _30;
};
KSYS_CHECK_SIZE_NX150(Unk_710235b408, 0x38);

// vtable 0x710235b700 (placeholder name; no RTTI of its own): the GuardianComponent's damage callback, forwarding to
// Guardian::sub_710003B564 with the component's part. `call` (0x7100040e9c) is the key function; D0 0x7100040e54.
class Unk_710235b700 : public DamageCallback {
public:
    explicit Unk_710235b700(GuardianComponent* owner) : mOwner(owner) {}
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, DamageCallbackInfo* a6) override;

    /* 0x28 */ GuardianComponent* mOwner;
    /* 0x30 */ u32 _30 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_710235b700, 0x38);

// Name from the CSV (GuardianComponent::*; the namespace is a guess). Direct child of DynamicActor: the RTTI static
// 0x71025af298 is initialised with the Derive<DynamicActor> vtable. ctor 0x710003bec0, factory 0x710003be7c.
// Declaration only (lane1 s47): the AI of the Guardian beam attack casts its actor to this class.
// TODO: incomplete (the members after +0xba8 are not modeled).
class GuardianComponent : public ksys::act::DynamicActor {
    SEAD_RTTI_OVERRIDE(GuardianComponent, DynamicActor)
public:
    // 0x710003be7c (CSV GuardianComponent::construct).
    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);
    explicit GuardianComponent(const CreateArg& arg);
    ~GuardianComponent() override;
    bool canWakeUp_() override;
    void preDelete2_(const PreDeleteArg& arg) override;
    void initMaybe() override;
    void updateMtxFromPhysics() override;
    void m63() override;
    void updatePositionMaybe() override;
    ksys::act::LifeRecoverInfo* getLifeRecoverInfo() override;
    void m147(sead::PtrArray<ksys::act::Actor>* actors) override;
    ksys::act::Actor* m31() override;
    bool m55() override;
    bool shouldUnload(s32* reason) override;

    // 0x710003d2b4 (placeholder name): the Guardian that owns this component (`_b90.getProc()` cast).
    Guardian* sub_710003D2B4();

    /* 0xb90 */ ksys::act::BaseProcLink _b90;
    // Full ctor 3BEC0 initializes the subtype selector to -1 and this pointer to
    // null. Full prepareInit_ 3C41C assigns one of five interface subtypes; full
    // preDelete2_ 3C6D8 calls its cleanup and deleting destructor, then clears it.
    // The part: 0 Cannon, 1 WeakPoint, 2 Leg, 3 BrokenLeg, 4 Propeller (from the actor name), else -1.
    /* 0xba0 */ s32 _ba0 = -1;
    /* 0xba8 */ GuardianComponentBind* _ba8 = nullptr;
    /* 0xbb0 */ ksys::phys::ContactPointInfo* _bb0 = nullptr;  // "Ground" contact points (m63)
    /* 0xbb8 */ Unk_710235b700 mDamageCallback{this};
};
KSYS_CHECK_SIZE_NX150(GuardianComponent, 0xbf0);

}  // namespace uking::act
