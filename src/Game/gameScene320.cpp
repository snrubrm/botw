#include "Game/gameScene320.h"
#include <cstring>
#include <controller/seadController.h>

GameScene320::GameScene320() = default;

GameScene320::~GameScene320() {
    _8 = nullptr;
}

void GameScene320::reset() {
    _10 = -1;
    _8 = nullptr;
    std::memset(&_14, 0, 13);
}

void GameScene320::sub_71008979B0(sead::Controller* a8, s32 a10, u8 a21, u8 a18) {
    _8 = a8;
    _10 = a10;
    _21 = a21;
    _18 = a18;
    _1c = 0;
    _20 = 0;
}

// NON_MATCHING: held-mask load and bit-shift scheduling differ inside the loop.
void GameScene320::sub_71008979E4() {
    if (!_8)
        return;
    if (++_1c >= _18) {
        _1c = 0;
        _20 = 0;
    }
    for (u32 i = 0; i < 32; ++i) {
        const u32 bit = 1u << i;
        if (_10 != 0 && (_8->getHoldMask() & bit) != 0)
            _14 |= bit;
    }
    if (_14 == _10) {
        _14 = 0;
        ++_20;
    }
}

bool GameScene320::sub_7100897A60() const {
    return _8 && _21 == _20;
}
