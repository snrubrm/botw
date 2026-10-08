#include "Game/gameGraphics.h"

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
