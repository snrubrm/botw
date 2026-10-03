#pragma once

#include <basis/seadTypes.h>

// Placeholder name (0x710070f974, no name known): a 0x18-byte state struct embedded at the end of
// LynelMove (+0x88) and LynelNavMeshMove (+0x80). Its constructor is out of line.
struct Unk_710070f974 {
    Unk_710070f974();
    ~Unk_710070f974();

    s32 _0 = 0;
    u64 _8 = 0;
    u64 _10 = 0;
};
