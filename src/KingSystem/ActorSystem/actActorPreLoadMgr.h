#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>

namespace ksys::act {

class Actor;

// Partial interface for pointer use; instance fields and full extent are not modeled.
class ActorPreLoadMgr {
    SEAD_SINGLETON_DISPOSER(ActorPreLoadMgr)
    ActorPreLoadMgr();
    ~ActorPreLoadMgr();

public:
    struct Entry;

    Entry* x(Actor* actor);
    void preloadActorMaybe(Entry* entry, const sead::SafeString& name);
    void sub_7100D58F28(Actor* actor);
};

}  // namespace ksys::act
