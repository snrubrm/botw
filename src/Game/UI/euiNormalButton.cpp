#include "Game/UI/euiButton.h"

namespace eui {

// 0x7100bd9db4
NormalButton::NormalButton(const NormalButton& other, LayoutEx* layout, sead::Heap* heap) {
    CloneImpl_(other, layout, heap);
}

}  // namespace eui
