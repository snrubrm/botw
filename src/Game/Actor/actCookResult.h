#pragma once

#include "Game/Actor/actItem.h"
#include "Game/Cooking/cookManager.h"

namespace uking::act {

// Name from the CSV (CookResult::*; the namespace is a guess). Child of Item (the factory 0x710000a118 calls
// the out-of-line Item ctor; the CSV row CookResult::construct at 0x710000a114 is the 4-byte `b` stub in front
// of it). RTTI static 0x71025ae690. The cooked item (`_bb0`) is named after the actor.
// TODO: incomplete (the setter 0x710000a3d0 and the other overrides are not written).
class CookResult : public Item {
    SEAD_RTTI_OVERRIDE(CookResult, Item)
public:
    explicit CookResult(const CreateArg& arg);

    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);

    /* 0xbb0 */ CookItem _bb0;
};
KSYS_CHECK_SIZE_NX150(CookResult, 0xdd8);

}  // namespace uking::act
