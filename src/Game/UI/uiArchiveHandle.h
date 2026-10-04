#pragma once

#include "KingSystem/Utils/Types.h"

namespace nn::ui2d {

// Handle of a loaded layout archive (CSV: nn::ui2d::ArchiveHandle). Only the size and the destructor are known:
// the destructor (0x71009c3358) destroys several placeholder objects and a base object at +0x30; it is not
// decompiled yet.
class ArchiveHandle {
public:
    ~ArchiveHandle();

private:
    u8 _0[0xb8];
};

}  // namespace nn::ui2d
