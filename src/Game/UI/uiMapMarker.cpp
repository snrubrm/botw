#include "Game/UI/uiUnkSingletons.h"

namespace uking::ui {

// 0x71009504f8
void UiSubsys1Entry::m4() {
    _3c &= ~0x777f;
    m11();
    m13();
}

// 0x710095053c
void UiSubsys1Entry::m5() {
    m12();
    m13();
}

// 0x7100950570
void UiSubsys1Entry::m6() {
    m14();
    m15();
}

// 0x71009505a4
void UiSubsys1Entry::m7() {
    m16();
    m17();
}

// 0x71009505d8
void UiSubsys1Entry::m8() {
    m20();
    m21();
}

// 0x710095060c
void UiSubsys1Entry::m9() {
    if (!(_3c & 8))
        _3c &= ~0x7566;
    _3c &= ~8;
}

// 0x710095062c
s32 UiSubsys1Entry::m10() {
    if ((_3c & 0x800) || _1c == 42)
        return (_3c >> 9) & 1;
    return 3;
}

// 0x7100951388
void UiSubsys1Entry::sub_7100951388(bool enabled) {
    _3c |= 8;
    m25(enabled);
}

}  // namespace uking::ui
