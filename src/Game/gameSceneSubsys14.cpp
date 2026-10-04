#include "Game/gameSceneSubsys14.h"

bool GameSceneSubsys14::sub_7100904ED4() const {
    return _168 & 1;
}

bool GameSceneSubsys14::sub_7100904EE0() const {
    return _168 & 0x20004;
}

bool GameSceneSubsys14::sub_7100904EF8() const {
    return _16c & 1;
}

bool GameSceneSubsys14::sub_7100904F04() const {
    return _16c >> 1 & 1;
}

bool GameSceneSubsys14::sub_7100904F10() const {
    return _16c >> 2 & 1;
}

bool GameSceneSubsys14::sub_7100904F1C() const {
    return _16c >> 3 & 1;
}

bool GameSceneSubsys14::sub_7100904F28() const {
    return _16c >> 4 & 1;
}

bool GameSceneSubsys14::sub_7100904F34() const {
    return _16c >> 5 & 1;
}

bool GameSceneSubsys14::sub_7100904F40() const {
    return _16c >> 6 & 1;
}

bool GameSceneSubsys14::sub_7100904F68() const {
    return _16c >> 8 & 1;
}
