#pragma once

#include <hostio/seadHostIONode.h>

namespace gsys {

// G3dResModelEx +0x18 is an array with stride 0x440 (ksys::tera 0x71011413b4); the destructor
// 0x7100c6d0fc is in a vtable and stores the vtable at +0.
class G3dResMaterialEx : public sead::hostio::Node {
public:
    virtual ~G3dResMaterialEx();

private:
    u8 _8[0x440 - 0x8];
};
static_assert(sizeof(G3dResMaterialEx) == 0x440);

}  // namespace gsys
