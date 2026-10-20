#pragma once

#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>

namespace gsys {

// Singleton with no state in this build (the disposer calls the destructor through slot 1, after
// the hostio::Node slot): createInstance allocates 0x28 bytes (vtable and the
// singleton disposer) and the destructor is empty.
class DebugCtrl : public sead::hostio::Node {
    SEAD_SINGLETON_DISPOSER(DebugCtrl)
public:
    DebugCtrl() = default;
    virtual ~DebugCtrl();
};
static_assert(sizeof(DebugCtrl) == 0x28);

}  // namespace gsys
