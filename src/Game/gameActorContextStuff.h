#pragma once

#include <basis/seadTypes.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}

// Name from the CSV. Carried-item context embedded in GameSceneSubsys12; layout incomplete.
class ActorContextStuff {
public:
    // 0x710065d8e4
    void sub_710065D8E4(sead::Heap* heap, bool a2);
    // 0x710065f044: number of entries in the carried-item array at +0x638.
    s32 sub_710065F044();
    // 0x710065f07c: number of active entries.
    s32 sub_710065F07C();
    // 0x710065f9ac
    void sub_710065F9AC();

    u8 _0[0x28];
    sead::CriticalSection _28;
    u8 _68[0x638 - 0x68];
    s32 _638;
    u8 _63c[0x760 - 0x63c];
};
KSYS_CHECK_SIZE_NX150(ActorContextStuff, 0x760);
