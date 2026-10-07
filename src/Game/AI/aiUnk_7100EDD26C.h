#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>

namespace ksys::act {
class Actor;
}

// Grab PodNode-name lookup (0x7100edd26c). Reads the actor's Grab GParam object (index 0x17) and
// returns the PodNode name of slot `index` (0 - 5), or the empty string if the list or object is
// missing or the index is out of range. Placeholder name.

// 0x7100edd26c
const sead::SafeString* sub_7100EDD26C(ksys::act::Actor* actor, int index);
