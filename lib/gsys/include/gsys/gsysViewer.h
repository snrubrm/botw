#pragma once

#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>

namespace gsys {

// Singleton with no state in this build (the disposer calls the destructor through slot 1, after
// the hostio::Node slot): createInstance allocates 0x28 bytes (vtable and the
// singleton disposer) and the destructor is empty.
class Viewer : public sead::hostio::Node {
    SEAD_SINGLETON_DISPOSER(Viewer)
public:
    Viewer() = default;
    virtual ~Viewer();
};
static_assert(sizeof(Viewer) == 0x28);

}  // namespace gsys
