#pragma once

#include <basis/seadTypes.h>
#include <mc/seadCoreInfo.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

// Argument of Actor vtable slot 117 (and of Actor::x_17, which forwards it to the actor's
// weapons / parts / connected calc child and parent). Built by Actor::doHandleMessage_,
// Actor::x_15 and two more wrappers: _0 is the kind (0, 2 or 3), _4 the current core number (the
// callee clamps it to < 3 and uses it as an index) and the other fields depend on the kind.
struct Unk117 {
    u32 _0 = 0;
    sead::CoreId _4;
    void* _8;   // kind 3
    void* _10;  // kind 0
    const char* _18;  // kind 0
};
KSYS_CHECK_SIZE_NX150(Unk117, 0x20);

}  // namespace ksys::act
