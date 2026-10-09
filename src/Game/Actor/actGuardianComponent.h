#pragma once

#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::act {

class Guardian;
class GuardianComponent;

// Declaration-only prefix of the component's heap bind interface. Whole 3BBB4 / 40750
// identify its independent RTTI root at 25AF258. The full 13-slot object table at
// 235B408 was read; slots after the destructor are not declared here because their
// parameter domains remain incomplete. Do not construct or emit this interface.
class GuardianComponentBind {
    SEAD_RTTI_BASE(GuardianComponentBind)
public:
    virtual ~GuardianComponentBind();

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

    /* 0x10 */ u8 _10[0x30 - 0x10];
    /* 0x30 */ f32 _30;
};
KSYS_CHECK_SIZE_NX150(Unk_710235b408, 0x38);

// Name from the CSV (GuardianComponent::*; the namespace is a guess). Direct child of DynamicActor: the RTTI static
// 0x71025af298 is initialised with the Derive<DynamicActor> vtable. ctor 0x710003bec0, factory 0x710003be7c.
// Declaration only (lane1 s47): the AI of the Guardian beam attack casts its actor to this class.
// TODO: incomplete (the members after +0xba8 are not modeled).
class GuardianComponent : public ksys::act::DynamicActor {
    SEAD_RTTI_OVERRIDE(GuardianComponent, DynamicActor)
public:
    explicit GuardianComponent(const CreateArg& arg);
    ~GuardianComponent() override;

    // 0x710003d2b4 (placeholder name): the Guardian that owns this component (`_b90.getProc()` cast).
    Guardian* sub_710003D2B4();

    /* 0xb90 */ ksys::act::BaseProcLink _b90;
    // Full ctor 3BEC0 initializes the subtype selector to -1 and this pointer to
    // null. Full prepareInit_ 3C41C assigns one of five interface subtypes; full
    // preDelete2_ 3C6D8 calls its cleanup and deleting destructor, then clears it.
    /* 0xba0 */ s32 _ba0;
    /* 0xba8 */ GuardianComponentBind* _ba8;
};

}  // namespace uking::act
