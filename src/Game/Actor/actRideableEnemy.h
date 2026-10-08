#pragma once

#include "Game/Actor/actRideable.h"

namespace uking::act {

// RideableEnemy (vtable 0x71023cf460). Own checkDerived (m0), getRuntimeTypeInfo (m1),
// D0 (m3) and m24 (empty); the original vtable's D1 slot points at Rideable::D1
// (no own D1). NOTE: our implicit D1 differs (it calls Rideable::D1 from our own
// COMDAT); the vtable is not tracked yet — revisit the dtor shape when m3 is done.
// TODO: incomplete (ctor, m23, m40, m45, m0, m1, m3, m44 not decompiled).
class RideableEnemy : public Rideable {
    SEAD_RTTI_OVERRIDE(RideableEnemy, Rideable)
public:
    void m24() override;
    bool m44() override;
    // Slot 45: the override of Unk_7100e8b2b8::procLink13 (RiddenAnimalType-gated speed factor; its thunk
    // 0x71002cb704 inlines the body, like RideableHorse's).
    f32 procLink13() override;
    HorseReins* m40() override;
};

}  // namespace uking::act
