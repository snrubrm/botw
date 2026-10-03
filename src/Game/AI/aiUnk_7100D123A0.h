#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace ksys::act {
class Actor;
}

namespace ksys::act::acc {

// Placeholder (CSV name `act::acc::Actor::navmeshStuff`, 0x7100d123a0; declared only): an ActorConstDataAccess
// typed for a generic Actor (the CSV puts its methods in a namespace `act::acc`). TODO: incomplete.
class Actor : public ActorConstDataAccess {
public:
    // Whether the accessed actor is on the navmesh around `self` (the two floats are distance tolerances).
    bool navmeshStuff(f32 dist, f32 dist_on_stop, ksys::act::Actor* self);
};

}  // namespace ksys::act::acc
