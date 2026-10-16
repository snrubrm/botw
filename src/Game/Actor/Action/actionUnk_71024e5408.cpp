#include "Game/Actor/Action/actionActorObserverBase.h"

// The observer's own TU (0x7100e28d58 - 0x7100e2906c): the constructor calls ActorObserverBase's constructor
// out of line, and the vtable (with the D1 / D0 at 0x7100e29068 / 0x7100e2906c) is emitted here.
// NON_MATCHING: the original first zeroes _28 (8 bytes) and the buffer pointer _20 before the final stores.
Unk_71024e5408::Unk_71024e5408(ksys::act::ai::ActionBase* owner)
    : ActorObserverBase(owner), _28{ksys::phys::ContactLayer::SensorChemicalElement} {
    _18.setBuffer(1, &_28);
}

// NON_MATCHING: C++17 evaluation order (the virtual m15 is loaded before the argument)
bool Unk_71024e5408::m3(const CollisionIterator& it) {
    return m15(getElementHolderMaybe((*it)->bodies[1]));
}

// NON_MATCHING: C++17 evaluation order (the virtual m15 is loaded before the argument)
bool Unk_71024e5408::m4(const ContactIterator& it) {
    return m15(getElementHolderMaybe((*it)->body_b));
}

bool Unk_71024e5408::m7(const CollisionIterator& it) {
    return getElementHolderMaybe((*it)->bodies[1]) != nullptr;
}

bool Unk_71024e5408::m8(const ContactIterator& it) {
    return getElementHolderMaybe((*it)->body_b) != nullptr;
}
