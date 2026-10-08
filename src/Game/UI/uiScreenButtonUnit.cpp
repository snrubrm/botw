#include "Game/UI/uiScreens.h"

// Kept out of uiScreenEx.cpp: the original calls these forwarders out of line.
namespace uking::ui {

// 0x7100939bd8
Unk_7102474e38::Unk_7102474e38() {}

// NON_MATCHING: vector assignment and flag-store scheduling differ.
// 0x7100939c18
Unk_7102474e38::~Unk_7102474e38() {
    _8 = 0;
    _10 = nullptr;
    _18 = nullptr;
    _20 = nullptr;
    _28 = nullptr;
    _30 = 0;
    _34 = sead::Vector2f::zero;
    _3c = -1;
    _40 = -1;
    _44 = -1;
}

// 0x7100939c5c
ScreenEx* Unk_7102474e38::sub_7100939C5C() const {
    return _20->mScreen;
}

s32 Unk_7102474e38::sub_7100939C68() const { return _18->mEntry->_2f0; }
// NON_MATCHING: multiplication operand loads and registers differ.
s32 Unk_7102474e38::sub_7100939C78() const {
    return _3c + _18->mEntry->_2a0 * _18->mRecord->_c * _18->mEntry->_2a4;
}
// NON_MATCHING: loop induction width and arithmetic scheduling differ.
bool Unk_7102474e38::sub_7100939CA0() const {
    s32 count = 0;
    if (_20->_290) {
        for (s32 i = 0; i < _18->mEntry->_2f0; ++i) {
            if (u32(i) < _20->_288 && _20->_290[i])
                count += _20->_290[i]->_29c;
        }
        count += _3c + _18->mEntry->_2a0 * _18->mRecord->_c * _18->mEntry->_2a4;
    }
    return _20->_2d8 == count;
}

// 0x7100939ef8
void Unk_7102474e38::sub_7100939EF8(eui::AnimButton* button) {
    m15(button);
}

// 0x7100939f04
void Unk_7102474e38::sub_7100939F04(eui::AnimButton* button) {
    m16(button);
}

// 0x7100939f10
void Unk_7102474e38::sub_7100939F10(eui::AnimButton* button) {
    m17(button);
}

// 0x7100939f1c
void Unk_7102474e38::sub_7100939F1C(eui::AnimButton* button) {
    m18(button);
}

// 0x7100939f28
void Unk_7102474e38::sub_7100939F28(eui::AnimButton* button) {
    m19(button);
}

// 0x7100939f34
void Unk_7102474e38::sub_7100939F34(eui::AnimButton* button) {
    m20(button);
}

// 0x7100939f40
void Unk_7102474e38::sub_7100939F40(eui::AnimButton* button) {
    m21(button);
}

// 0x7100939f4c
void Unk_7102474e38::sub_7100939F4C(eui::AnimButton* button) {
    m22(button);
}

// The eight original default button notifications are empty.
void Unk_7102474e38::m4(sead::Heap*) {}
void Unk_7102474e38::m5() {}
void Unk_7102474e38::m6() {}
void Unk_7102474e38::m7() {}
void Unk_7102474e38::m8() {}
void Unk_7102474e38::m9() {}
void Unk_7102474e38::m10() {}
void Unk_7102474e38::m11() {}
void Unk_7102474e38::m12() {}
void Unk_7102474e38::m13() {}
void Unk_7102474e38::m14() {}

void Unk_7102474e38::m15(eui::AnimButton*) {}
void Unk_7102474e38::m16(eui::AnimButton*) {}
void Unk_7102474e38::m17(eui::AnimButton*) {}
void Unk_7102474e38::m18(eui::AnimButton*) {}
void Unk_7102474e38::m19(eui::AnimButton*) {}
void Unk_7102474e38::m20(eui::AnimButton*) {}
void Unk_7102474e38::m21(eui::AnimButton*) {}
void Unk_7102474e38::m22(eui::AnimButton*) {}

}  // namespace uking::ui
