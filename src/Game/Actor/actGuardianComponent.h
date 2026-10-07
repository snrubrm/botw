#pragma once

#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::act {

class Guardian;

// Name from the CSV (GuardianComponent::*; the namespace is a guess). Direct child of DynamicActor: the RTTI static
// 0x71025af298 is initialised with the Derive<DynamicActor> vtable. ctor 0x710003bec0, factory 0x710003be7c.
// Declaration only (lane1 s47): the AI of the Guardian beam attack casts its actor to this class.
// TODO: incomplete (the members between DynamicActor and +0xb90 / +0xba8 are not modelled).
class GuardianComponent : public ksys::act::DynamicActor {
    SEAD_RTTI_OVERRIDE(GuardianComponent, DynamicActor)
public:
    explicit GuardianComponent(const CreateArg& arg);
    ~GuardianComponent() override;

    // 0x710003d2b4 (placeholder name): the Guardian that owns this component (`_b90.getProc()` cast).
    Guardian* sub_710003D2B4();

    /* 0xb90 */ ksys::act::BaseProcLink _b90;
};

}  // namespace uking::act
