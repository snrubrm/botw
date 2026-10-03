#pragma once

namespace ksys::act {
class Actor;
class ActorConstDataAccess;
}  // namespace ksys::act

// Unnamed free helper (placeholder name; ~5 callers: RideHorseAI::enter_ ...).

// 0x7100e81220: acquires the actor linked by the actor's rider info (getPlayerRideInfo()->_18); false
// when it has none.
bool sub_7100E81220(ksys::act::Actor* actor, ksys::act::ActorConstDataAccess* accessor);
