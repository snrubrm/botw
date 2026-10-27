#include "Game/gameDebugSubsys.h"

DebugSubsys1::~DebugSubsys1() = default;

void DebugSubsys1::initBeforeStageGen() {
    _108 = 0;
    _110 = 0;
    _118 = 0;
    _120 = 0;
    _128 = 0;
}

void DebugSubsys1::x(bool on) {
    _20 = on;
}
