#pragma once

#include "KingSystem/ActorSystem/actActor.h"

namespace uking::act {

// Name from the CSV (UserEdgeActor::*; the namespace is a guess). Factory 0x7100e8f660: new(0x850).
// RTTI static 0x7102603e08, vtable 0x71024ed780 (GOT value). Owns an array of 0xa0-byte physics objects
// (UserTag-like, destroyed in m20). Only the factory and the destructor are written so far.
class UserEdgeActor : public ksys::act::Actor {
    SEAD_RTTI_OVERRIDE(UserEdgeActor, ksys::act::Actor)
public:
    explicit UserEdgeActor(const CreateArg& arg);
    ~UserEdgeActor() override;

    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);

    // An 8-aligned struct: a plain u32 would be placed in Actor's tail padding (0x83c).
    struct Elements {
        /* 0x0 */ u32 mCount = 0;
        /* 0x8 */ void* mArray = nullptr;  // 0xa0-byte elements
    };
    /* 0x840 */ Elements _840;
};
KSYS_CHECK_SIZE_NX150(UserEdgeActor, 0x850);

}  // namespace uking::act
