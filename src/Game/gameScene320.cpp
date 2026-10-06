#include "Game/gameScene320.h"
#include <cstring>

GameScene320::GameScene320() = default;

GameScene320::~GameScene320() {
    _8 = nullptr;
}

void GameScene320::reset() {
    _10 = -1;
    _8 = nullptr;
    std::memset(&_14, 0, 13);
}

void GameScene320::sub_71008979B0(void* a8, s32 a10, u8 a21, u8 a18) {
    _8 = a8;
    _10 = a10;
    _21 = a21;
    _18 = a18;
    _1c = 0;
    _20 = 0;
}
