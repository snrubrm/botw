#pragma once

#include <basis/seadTypes.h>

// Placeholder name (0x7100d3d3a8, no name known): a 0x20-byte state struct embedded at the end of
// several action classes (Kick at 0x88, AirOctaFloat, ApplyMoveTrigger, EnemyChangeWeapon). Its
// constructor is out of line and called from their constructors.
struct Unk_7100d3d3a8 {
    Unk_7100d3d3a8();

    u16 _0 = 0;
    u16 _2 = 1;
    u8 _4 = 0;
    void* _8 = nullptr;
    void* _10 = nullptr;
    void* _18 = nullptr;
};
