#include "KingSystem/Event/evtActorBase.h"

namespace ksys::evt {

// 0x71008a8b78
Actor::Actor(ActorBinding* binding, EventActorSet* set, sead::Heap* heap) : ActorBase(binding, set, heap) {}

// D1 0x71008a8bac, D0 0x71008a8e68
Actor::~Actor() {
    sub_71008A8BE0();
}

}  // namespace ksys::evt
