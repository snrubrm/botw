#include "Game/UI/euiLayoutEx.h"
#include <new>

namespace eui {

// 0x7100bdd16c
LayoutEx::LayoutEx(Screen* screen) : mScreen(screen) {}

// NON_MATCHING: the original snapshots mScreen before allocation; this natural body reads it at construction.
// 0x7100bdf0f0
LayoutEx* LayoutEx::m21() {
    void* memory = nn::ui2d::Layout::AllocateMemory(sizeof(LayoutEx), 4);
    if (!memory)
        return nullptr;
    return new (memory) LayoutEx(mScreen);
}

// 0x7100bdd41c
Animator* LayoutEx::createAnimatorAuto(const char* name, bool b) {
    return tryCreateAnimatorAuto(name, b);
}

// 0x7100bdd980
Animator* LayoutEx::tryCreateAnimatorAutoWithWarning(const char* name, bool b) {
    return tryCreateAnimatorAuto(name, b);
}

}  // namespace eui
