#pragma once

#include <basis/seadTypes.h>

namespace ksys::act {
class ActorConstDataAccess;
}

// 0x710001a69c (lane3 s18; also called by the AI classes TargetAngerSelect and
// LastAttackerSpecialActionSelect): whether the accessor's actor is an Enemy and any of the flag
// bits `flags` are set in Enemy::_e84.
bool sub_710001A69C(const ksys::act::ActorConstDataAccess* accessor, u32 flags);
