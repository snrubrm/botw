#pragma once

#include <prim/seadSafeString.h>
#include "Game/AI/aiUnk_71007024d4.h"

namespace sead {
class Heap;
}

// Placeholder name (vtable 0x71023f18e8, no RTTI): the actor "rain" component embedded at
// GanonBeastRoot + 0x50 (the "GrudeRainObject" / "GrudeRainObject2" static params live inside it).
// Slots: m0 / m4 / m5 default (Unk_71007024d4); m1 / m2 / m3 / m5 / m6 below.
//
// Its random cycle helper (0x71007a921fc / 0x7100a92208 / 0x7100a92248, 12 bytes) has no known class.
class Unk_7100a921fc {
public:
    // 0x7100a92208: `count` entries; starts at a random one.
    void sub_7100A92208(s32 count);
    // 0x7100a92248: advances to the next entry (restarting at a random one after a full cycle);
    // returns whether the entry before was the last one.
    bool sub_7100A92248();

    Unk_7100a921fc();

    /* 0x0 */ s32 _0 = 0;
    /* 0x4 */ s32 _4 = 0;
    /* 0x8 */ s32 _8 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_7100a921fc, 0xc);

class Unk_71023f18e8 : public Unk_71007024d4 {
public:
    Unk_71023f18e8() { _60.sub_7100A92208(2); }

    // The original has a non-trivial (empty) destructor whose vtable store is kept when it is inlined
    // into GanonBeastRoot::~GanonBeastRoot.
    ~Unk_71023f18e8() { ; }

    // 0x71003e6704: the player position.
    bool m1(sead::Vector3f* out) override;
    // 0x71003e69e8: the name of the next actor ("GrudeRainObject" / "GrudeRainObject2").
    bool m2(sead::BufferedSafeString* out) override;
    // 0x1543c0 (nullsub)
    void m3(ksys::act::Actor* actor) override {}
    // 0x71003e6740
    void m5(f32* radius, f32* angle, const sead::Vector3f* base) override;
    // 0x71003e6948: the player position plus 24 frames of velocity.
    void m6(sead::Vector3f* out) override;

    /* 0x40 */ sead::SafeString mGrudeRainObject_s;
    /* 0x50 */ sead::SafeString mGrudeRainObject2_s;
    /* 0x60 */ Unk_7100a921fc _60;
    /* 0x6c */ bool _6c = false;
    /* 0x6d */ bool _6d = false;
};
KSYS_CHECK_SIZE_NX150(Unk_71023f18e8, 0x70);
