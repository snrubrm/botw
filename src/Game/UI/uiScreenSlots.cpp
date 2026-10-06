#include "Game/UI/uiScreens.h"

// Trivial virtual slots of uking::ui::Screen / ScreenEx (the 0x7100009cf8a4 block of 4-byte functions).
namespace uking::ui {

void Screen::m69() {}
void Screen::m70() {}
void Screen::m71() {}
void Screen::m82() {}
void Screen::m83() {}
void Screen::m84() {}
void Screen::m85() {}
void Screen::m86() {}
void Screen::m87() {}
void Screen::m88() {}
void Screen::m90() {}
void Screen::m91() {}
void Screen::m92(sead::Heap*) {}
void Screen::m95() {}
void Screen::m101() {}
void Screen::m102(eui::AnimButton*) {}
void Screen::m103(eui::AnimButton*) {}
void Screen::m104(eui::AnimButton*) {}
void Screen::m105(eui::AnimButton*) {}
void Screen::m106(eui::AnimButton*) {}
void Screen::m107(eui::AnimButton*) {}
void Screen::m108(eui::AnimButton*) {}
void Screen::m109(eui::AnimButton*) {}
void Screen::m110() {}
s32 Screen::m72() {
    return 0;
}

s32 Screen::m81() {
    return 0;
}

void Screen::m96() {
    open(1);
}

void Screen::m97() {
    close(-1);
}

void ScreenEx::m127() {}
void ScreenEx::m128() {}
void ScreenEx::m129() {}
void ScreenEx::m130() {}
void ScreenEx::m131(void*) {}
void ScreenEx::m132(void*) {}
void ScreenEx::m133(void*, void*) {}
void ScreenEx::m134(void*, void*) {}
void ScreenEx::m135(void*, void*) {}
void ScreenEx::m136(void*, void*) {}
void ScreenEx::m137(void*, void*) {}
void ScreenEx::m138(void*, void*) {}
void ScreenEx::m139(void*, void*) {}
void ScreenEx::m140(void*, void*) {}
s32 ScreenEx::m141(const ksys::Message&) {
    return 0;
}

s32 ScreenEx::m142(const ksys::Message&) {
    return 0;
}

void* ScreenEx::m143() {
    return nullptr;
}

// 0x7100a00584
void Screen::m93(sead::Heap*) {}

// 0x7100a03e18
void Screen::m94() {}

// 0x7100a00588
void Screen::m98() {}

// 0x71009d6c20
void Screen::m99() {}

// 0x71009f2eac
void Screen::m100() {}

}  // namespace uking::ui
