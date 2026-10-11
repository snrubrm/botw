#include "Game/UI/uiUnkSingletons.h"
#include "KingSystem/GameData/gdtManager.h"

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

// NON_MATCHING: the base reset remains out-of-line and its TU default objects are not modeled.
Unk_71024754c0::~Unk_71024754c0() {
    _50 = nullptr;
    _58 = nullptr;
    _60 = 0;
}

void Unk_71024754c0::m4() {
    m31();
    _3c &= ~0x777f;
    m11();
    m13();
}

void Unk_71024754c0::m5() {
    m32();
    m12();
    m13();
}

void Unk_71024754c0::m9() {
    if (!(_3c & 8))
        _3c &= ~0x7566;
    _3c &= ~0x10008;
}

void Unk_71024754c0::m11() {
    if (!_58)
        return;
    _60 = _58->_1c;
    _3c = _60 > 0 ? _3c | 0x8000 : _3c & ~0x8000;
    m25((_3c & 0x8000) != 0);
    _3c = (_3c & 0x8000) ? _3c | 0x80 : _3c & ~0x80;
}

void Unk_71024754c0::m12() {
    _3c = (_3c & 0x8000) ? _3c | 0x80 : _3c & ~0x80;
}

void Unk_71024754c0::m30() {
    auto* entry = _58;
    if (entry && entry->_10 && *entry->_10)
        entry->_18 = ksys::gdt::Manager::instance()->getS32Handle(entry->_10);
}

void Unk_71024754c0::m31() {
    _3c &= ~0x10000;
    if (!_58)
        return;
    _60 = _58->_1c;
    _3c = _60 > 0 ? _3c | 0x8000 : _3c & ~0x8000;
    m25((_3c & 0x8000) != 0);
    _3c = (_3c & 0x8000) ? _3c | 0x80 : _3c & ~0x80;
}

void Unk_71024754c0::m32() {
    if (!_58 || !ksys::gdt::Manager::instance()->getParam().get().getBuffer0()->hasCopiedS32Flags())
        return;
    _60 = _58->_1c;
    _3c = ((_60 > 0) != ((_3c & 0x8000) != 0)) ? _3c | 0x10000 : _3c & ~0x10000;
    if (_3c & 0x10000)
        _3c = _60 > 0 ? _3c | 0x8000 : _3c & ~0x8000;
}

bool UiSubsys1Entry::sub_7100951048() const {
    return _24 == 0;
}

// NON_MATCHING: cleanup keeps an extra address register across the control call.
void UiSubsys1Entry::m22() {
    if (_8) {
        _8->_18 = nullptr;
        _8->sub_710098CF9C();
    }
    _8 = nullptr;
    _10 = nullptr;
    _18 = -1.0f;
}

// NON_MATCHING: inlined base cleanup keeps an extra address register.
void Unk_71024754c0::m22() {
    UiSubsys1Entry::m22();
    if (_50) {
        _50->_18 = nullptr;
        _50->sub_710098CF9C();
    }
    _50 = nullptr;
}

}  // namespace uking::ui
