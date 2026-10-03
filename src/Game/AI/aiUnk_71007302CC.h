#pragma once

#include <basis/seadTypes.h>

namespace ksys::act {
class Actor;
class BaseProcLink;
}  // namespace ksys::act

// Distance checks of an unnamed AI utility translation unit (0x71007302cc). Names are placeholders.

/// 0x71007302cc: whether the two actors are at most `distance` apart.
bool sub_71007302CC(ksys::act::Actor* a, ksys::act::Actor* b, f32 distance);
/// 0x71007303f0: the same for two linked actors.
bool sub_71007303F0(ksys::act::BaseProcLink* a, ksys::act::BaseProcLink* b, f32 distance);
