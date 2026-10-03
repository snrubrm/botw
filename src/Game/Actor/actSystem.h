#pragma once

#include "KingSystem/ActorSystem/actActor.h"

namespace uking::act {

// Name from the CSV (System::*; the namespace is a guess). Factory 0x7100eda718: new(0x840) + inlined ctor (sets
// _1c0 = 6). RTTI static 0x7102606918.
// TODO: incomplete (no members / further overrides known yet).
class System : public ksys::act::Actor {
    SEAD_RTTI_OVERRIDE(System, ksys::act::Actor)
public:
    explicit System(const CreateArg& arg);
    ~System() override;

    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);

protected:
    bool prepareInit_(sead::Heap* heap, PrepareArg& arg) override;

public:
    bool shouldUnload(s32* a1) override;
    // New virtual (vtable slot 148, signature unknown; the secondary vtable offsets are 8 bytes larger).
    virtual void m148() {}
};
KSYS_CHECK_SIZE_NX150(System, 0x840);

}  // namespace uking::act
