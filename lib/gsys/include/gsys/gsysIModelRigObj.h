#pragma once

#include <container/seadListImpl.h>

namespace gsys {

class ModelUnit;

// Independent LightRigObj table 0x71024cf510 has only the update entry;
// its thunk 0x7100c5860c adjusts the actual +0x300 base. The constructor
// zeros its ListNode at +0x308 and begins the next owned node at +0x318.
// The game light record adds its own virtual destructor and debug method.
class IModelRigObj {
public:
    // Name/order inferred from the real 0x7100c44994 dispatch. The u16 mask
    // follows ModelUnit's existing visibility protocol and both native update
    // implementations; the native ABI alone cannot distinguish it from u32
    // when all producers already restrict the value to sixteen bits.
    virtual void update(ModelUnit* unit, u16 visibility_mask, f32 delta_time);

protected:
    // Model::pushBack uses the offset 8 initialized by 0x7100bf6ebc.
    sead::ListNode mModelNode;
};
static_assert(sizeof(IModelRigObj) == 0x18);

}  // namespace gsys
