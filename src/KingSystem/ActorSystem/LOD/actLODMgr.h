#pragma once

#include <heap/seadDisposer.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

// Name from the CSV (LODMgr::createInstance 0x710125184c, instance pointer 0x71026531b8; size 0x2a60;
// TU 0x7101250ed8 - 0x7101252xxx together with LodState's later methods). Only the frame counter is
// declared so far; the constructor (inlined in createInstance) is not decompiled.
class LODMgr {
    SEAD_SINGLETON_DISPOSER(LODMgr)
    LODMgr();
    virtual ~LODMgr();

public:
    /* 0x028 */ u8 _28[0x21a0 - 0x28];
    /* 0x21a0 */ s32 _21a0;
    /* 0x21a4 */ u8 _21a4[0x2a60 - 0x21a4];
};
KSYS_CHECK_SIZE_NX150(LODMgr, 0x2a60);

}  // namespace ksys::act
