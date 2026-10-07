#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>

namespace ksys::act {
class Actor;
}

// Node-name lookup in the translation unit at 0x710072dxxx. Reads the actor's GiantArmorSlot
// GParam object (index 0x38) and returns the node name of slot `index` (0 - 3), or the empty
// string if the index is out of range. Placeholder name.

// 0x710072d608
const sead::SafeString* sub_710072D608(ksys::act::Actor* actor, int index);
