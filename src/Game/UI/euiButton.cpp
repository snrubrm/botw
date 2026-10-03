#include "Game/UI/euiButton.h"

namespace eui {

// 0x7100bd73ec
void ButtonBase::ForceOff() {
    _40 = 0;
    setState(0);
}

// 0x7100bd7400
void ButtonBase::ForceOn() {
    _40 = 0;
    setState(3);
}

// 0x7100bd7414
void ButtonBase::ForceDown() {
    _40 = 0;
    setState(5);
}

}  // namespace eui
