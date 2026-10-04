#include "Game/UI/euiButton.h"

namespace eui {

// 0x7100beff6c
void HoverButton::Down() {
    if (mFlags & 0x40)
        Off();
}

}  // namespace eui
