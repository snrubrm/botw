#pragma once

#include <basis/seadTypes.h>

namespace ksys::act {
class Actor;
class BaseProcLink;
}  // namespace ksys::act

// Free function of an unnamed AI utility translation unit (0x710073cdfc). Name is a placeholder.

/// Index in `actor`'s drop table of the linked actor's General ChangeDropTableName (-1 if the link
/// has no actor or the name is empty).
s32 sub_710073CDFC(ksys::act::Actor* actor, ksys::act::BaseProcLink* link);
