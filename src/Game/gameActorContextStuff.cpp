#include "Game/gameActorContextStuff.h"

#include <prim/seadScopedLock.h>
s32 ActorContextStuff::sub_710065F044() {
    sead::ScopedLock<sead::CriticalSection> lock(&_28);
    return _638;
}
