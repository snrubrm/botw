#pragma once

#include <heap/seadDisposer.h>

namespace ksys::act {

class Actor;

// Partial interface for pointer use; instance fields and full extent are not modeled.
class DropMgr {
    SEAD_SINGLETON_DISPOSER(DropMgr)
    DropMgr();
    ~DropMgr();

public:
    void createDrops(Actor* actor, bool flag);
};

}  // namespace ksys::act
