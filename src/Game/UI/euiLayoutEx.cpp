#include "Game/UI/euiLayoutEx.h"

namespace eui {

// 0x7100bdd16c
LayoutEx::LayoutEx(Screen* screen) : mScreen(screen) {}

// 0x7100bdd41c
Animator* LayoutEx::createAnimatorAuto(const char* name, bool b) {
    return tryCreateAnimatorAuto(name, b);
}

// 0x7100bdd980
Animator* LayoutEx::tryCreateAnimatorAutoWithWarning(const char* name, bool b) {
    return tryCreateAnimatorAuto(name, b);
}

}  // namespace eui
