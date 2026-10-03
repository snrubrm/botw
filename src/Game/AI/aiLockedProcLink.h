#pragma once

#include <math/seadVector.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::ai {

// A CriticalSection followed by a BaseProcLink and a u32. Name and members are guesses.
// Evidence for it being one object: in the destructors of NPCTravelerRoot, NPCTravel, NPCHorseRide
// the original computes the address of the CriticalSection before the vtable store and keeps it
// across the BaseProcLink::reset() call (as it does for a sub-object destructor); separate members
// do not reproduce that.
struct LockedProcLinkMaybe {
    sead::CriticalSection mLock;
    ksys::act::BaseProcLink mLink;
    f32 _50 = 0.0f;
};

// A CriticalSection followed by a Vector3f (name and members are guesses). Used in pairs by
// NPCHorseRide and NPCHorseRideWait; its destructor is inlined (the CriticalSection destructor call).
struct LockedVectorMaybe {
    sead::CriticalSection mLock;
    sead::Vector3f _40;
};
static_assert(sizeof(LockedVectorMaybe) == 0x50);

}  // namespace uking::ai
