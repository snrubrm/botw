#pragma once

#include "KingSystem/ActorSystem/actActor.h"

namespace uking::act {

// Names from the CSV (HorseObject::m2 / m3 at 0x7100e7b234 / 0x7100e7b354 and HorseReins::m2 / m3 at
// 0x7100e7bcfc / 0x7100e7be1c are their `checkDerivedRuntimeTypeInfo` / `getRuntimeTypeInfo` virtuals,
// from the vtable analysis; the namespace is a guess). Direct children of Actor (both RTTI statics are
// initialised with the Derive<Actor> vtable): HorseObject = RTTI static 0x71025ae9e0 (HorseBase::_840 /
// _850, cast in HorseBase::m117, HorseManeCollarSyncAction ...), HorseReins = RTTI static 0x71025ae9d0
// (HorseBase::_860 / _870 / _880, cast in HorseBase::m117, HorseReinsBindAction, HorseSaddleBindAction,
// HorseManeGrabbedAction ...). Layout / virtuals not known yet (declared for sead::DynamicCast only).
class HorseObject : public ksys::act::Actor {
    SEAD_RTTI_OVERRIDE(HorseObject, ksys::act::Actor)
};

class HorseReins : public ksys::act::Actor {
    SEAD_RTTI_OVERRIDE(HorseReins, ksys::act::Actor)
};

}  // namespace uking::act
