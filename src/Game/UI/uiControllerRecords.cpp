#include <controller/seadControllerBase.h>
#include "Game/UI/uiUnkTiny.h"
#include <math/seadBoundBox.h>
#include <prim/seadSafeString.h>

namespace uking::ui {

// The UI controller's control-region records. Their constructors, getters and destructors sit together
// at 0x7100a6caf8 - 0x7100a6cc54, in a different TU from the controller's own methods
// (0x7100a6bf14 - 0x7100a6caf4), which is why the controller calls getBounds() out of line.

// 0x7100a6caf8
Unk_710249c3b0::Unk_710249c3b0() {
    _8 |= 2;
}

// 0x7100a6cb74
sead::BoundBox2f* Unk_710249c3b0::getBounds() {
    return &mBounds;
}

// 0x7100a6cb6c
Unk_710249c3b0::~Unk_710249c3b0() = default;

// 0x7100a6cb7c
// NON_MATCHING: the original pairs the stores as 0x10 / 0x14 and 0x18 / 0x1c (ours: 0xc / 0x10, 0x14 / 0x18)
Unk_710249c3d0::Unk_710249c3d0() = default;

// 0x7100a6cbb8
Unk_710249c3d0::~Unk_710249c3d0() = default;

// 0x7100a6cbc0
sead::BoundBox2f* Unk_710249c3d0::getBounds() {
    return &mBounds;
}

// 0x7100a6cbc8
Unk_710249c3f0::Unk_710249c3f0()
    : _28(sead::ControllerBase::cInvalidPointer), _30(sead::ControllerBase::cInvalidPointer) {}

// 0x7100a6cc44
Unk_710249c3f0::~Unk_710249c3f0() = default;

// 0x7100a6cc4c
sead::BoundBox2f* Unk_710249c3f0::getBounds() {
    return &mBounds;
}

// 0x7100a6cc54
u8 Unk_710249c3f0::get9() const {
    return _9;
}

}  // namespace uking::ui
