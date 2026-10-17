#include "Game/gameStruct30.h"

SEAD_SINGLETON_DISPOSER_IMPL(Struct30)

Struct30::~Struct30() = default;

void Struct30::setIsTitleMonitoringOrDemo(bool value) {
    mIsTitleMonitoringOrDemo = value;
}

void Struct30::setField29(bool value) {
    _29 = value;
}

u8 Struct30::getField2B() const {
    return _2b;
}

bool Struct30::isPanicBloodMoon() const {
    return mIsPanicBloodMoon;
}

void Struct30::setIsPanicBloodMoon(bool value) {
    mIsPanicBloodMoon = value;
}
