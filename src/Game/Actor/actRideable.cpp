#include "Game/Actor/actRideable.h"

namespace uking::act {

Rideable::Rideable() = default;

Rideable::~Rideable() = default;

void Rideable::m24() {
    RideableBase::_8 &= ~0x400u;
}

void* Rideable::m40() {
    return nullptr;
}

void Rideable::m42(int a1) {}

}  // namespace uking::act
