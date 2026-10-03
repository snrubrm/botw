#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include "KingSystem/Utils/Types.h"

namespace uking {

// Name from the CSV (Rumble::createInstance 0x7100897b74, deleteInstance 0x7100897c28, `__auto0`
// 0x7100897fe4). A sead singleton (size 0xa0, instance pointer at GOT 0x257a0d0 = 0x71026...) that
// starts controller rumble patterns; 24+ callers (Player damage actions, ControllerRumble, ...).
// Only what the callers use is declared; the member layout is not modelled.
class Rumble {
    SEAD_SINGLETON_DISPOSER(Rumble)
    Rumble();
    virtual ~Rumble();

public:
    // 0x7100897fe4 (CSV Rumble::__auto0, declaration only; placeholder name): starts the rumble pattern
    // `pattern` (an index into a table of 0x10-byte entries at 0x71025d0370; takes it by value through a
    // stack slot, so probably a SEAD_ENUM) `count` times unless a stronger pattern is already running.
    void sub_7100897FE4(s32 pattern, s32 count);
};

}  // namespace uking
