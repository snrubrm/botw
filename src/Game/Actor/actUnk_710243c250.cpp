#include "Game/Actor/actGuardian.h"
#include "Game/Actor/actGuardianRegistry.h"

Unk_710243c250::Unk_710243c250(ksys::act::Actor* owner)
    : sead::TListNode<Unk_710243c250*>(this) {
    _28.acquire(owner, false);
    _40 = -1;
}

Unk_710243c250::~Unk_710243c250() = default;

// NON_MATCHING: vtable and first bucket list stores are scheduled differently.
Unk_710243c280::Unk_710243c280() = default;

Unk_710243c280::~Unk_710243c280() = default;

Unk_710243c2a0::~Unk_710243c2a0() = default;
