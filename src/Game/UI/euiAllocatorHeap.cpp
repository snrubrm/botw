#include "Game/UI/euiLayoutEx.h"
#include <nn/ui2d/Layout.h>

namespace eui {

// 0x7100befa64
sead::Heap* GetNwAllocatorHeap() {
    return static_cast<sead::Heap*>(nn::ui2d::Layout::g_pUserData);
}

}  // namespace eui
