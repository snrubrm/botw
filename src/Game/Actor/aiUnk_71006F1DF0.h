#pragma once

#include <math/seadVector.h>

namespace ksys::act {
class Actor;
}

// Placeholder name = address (lane2 s21; 0x71006f1df0): whether `pos` is in a non-auto-placement zone, for an
// actor that has a rideable part (Actor slot 132) and is not a domestic animal. Used by PreyNormal::m39.
bool sub_71006F1DF0(ksys::act::Actor* actor, const sead::Vector3f& pos);
