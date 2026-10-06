#include "Game/gameScene320.h"
#include <cstring>

GameScene320::GameScene320() = default;

GameScene320::~GameScene320() {
    _8 = nullptr;
}

void GameScene320::reset() {
    _10 = -1;
    _8 = nullptr;
    std::memset(_14, 0, sizeof(_14));
}
