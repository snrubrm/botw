#pragma once

#include <basis/seadTypes.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Utils/Types.h"

// Placeholder declaration (lane3 s23; name from the CSV: createInstance 0x71006623f0, ctor 0x7100662478, ~70 unnamed
// users, e.g. Carried::calc_, CarryBox, DemoCookPotCook, Player::m76): the scene subsystem that handles carried
// items. A sead singleton (disposer at +0x18, size 0xc00); only the instance pointer and the flag word that the
// carry actions read are declared. Layout incomplete.
class GameSceneSubsys12 {
public:
    static GameSceneSubsys12* instance() { return sInstance; }

    u8 _0[0xa78];
    /* 0xa78 */ sead::Atomic<u32> _a78;
    u8 _a7c[0xc00 - 0xa7c];

    // 0x71025c5a00
    static GameSceneSubsys12* sInstance;
};
static_assert(sizeof(GameSceneSubsys12) == 0xc00);
