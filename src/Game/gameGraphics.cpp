#include "Game/gameGraphics.h"
#include <prim/seadScopedLock.h>

void Graphics::sub_7100F35FA4(bool value, bool second) {
    if (second)
        _284.changeBit(12, value);
    else
        _284.changeBit(11, value);
    _280 |= 1;
}

void Graphics::sub_7100F2E06C() {
    _284.setBit(22);
}

void Graphics::sub_7100F2AF70(u8 map) {
    auto lock = sead::makeScopedLock(_f18);
    _f59 = map;
}

void Graphics::sub_7100F2AFAC(u8 value) {
    auto lock = sead::makeScopedLock(_f18);
    _f5b = value;
}

void Graphics::sub_7100F2AFE8(u8 value) {
    auto lock = sead::makeScopedLock(_f18);
    _f5d = value;
}

void Graphics::sub_7100F2B024(u8 value) {
    auto lock = sead::makeScopedLock(_f18);
    _f5f = value;
}

f32 Graphics::sub_7100F35F28() const {
    return _378->_18->_1520;
}

f32 Graphics::sub_7100F35F38() const {
    return _378->_18->_1524;
}
