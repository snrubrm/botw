#pragma once

#include "KingSystem/ActorSystem/actActor.h"

namespace uking::act {

// Name from the CSV (HavokActiveObject::*; the namespace is a guess). Factory 0x7100080380: new(0x840) + inlined ctor (sets
// _1c0 = 3). RTTI static 0x71025afcf8.
// TODO: incomplete (no members / further overrides known yet).
class HavokActiveObject : public ksys::act::Actor {
    SEAD_RTTI_OVERRIDE(HavokActiveObject, ksys::act::Actor)
public:
    explicit HavokActiveObject(const CreateArg& arg);

    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);
};
KSYS_CHECK_SIZE_NX150(HavokActiveObject, 0x840);

}  // namespace uking::act
