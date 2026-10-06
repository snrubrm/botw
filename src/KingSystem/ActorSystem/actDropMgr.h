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
    // 0x7100d2c024 (CSV DropMgr::__auto2; declaration only, placeholder name): tests whether drops can be
    // created for `actor` (DropMgr::x on its drop table).
    bool sub_7100D2C024(Actor* actor);
};

}  // namespace ksys::act
