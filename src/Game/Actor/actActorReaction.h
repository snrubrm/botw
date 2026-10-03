#pragma once

#include "KingSystem/ActorSystem/actActor.h"

namespace uking::act {

// Name from the CSV (ActorReaction::*; the namespace is a guess). Factory 0x7100ebf620: new(0x840) + inlined
// ctor (clears the PreCalc job handler, sets _1c0 = 2). RTTI static 0x71026064a8.
// TODO: incomplete (no members / further overrides known yet).
class ActorReaction : public ksys::act::Actor {
    SEAD_RTTI_OVERRIDE(ActorReaction, ksys::act::Actor)
public:
    explicit ActorReaction(const CreateArg& arg);
    ~ActorReaction() override;

    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);

    // New virtual (vtable slot 148, signature unknown; the secondary vtable offsets are 8 bytes larger).
    virtual void m148() {}
};
KSYS_CHECK_SIZE_NX150(ActorReaction, 0x840);

}  // namespace uking::act
