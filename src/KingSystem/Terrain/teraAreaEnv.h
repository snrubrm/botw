#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/Utils/Types.h"

namespace gsys {
class ModelSceneEnv;
}

namespace ksys::tera {

// The game-side area environment getter (vtable 0x71025041b8). The constructor 0x710107c0f4 takes a
// gsys::ModelSceneEnv, stores it at +0x8 and clears the 0x48 bytes at +0x10. The three lookups below
// read the tables of the object at +0x10 (a 0x2c0 byte record built by 0x710107c124).
class AreaEnvGetter {
public:
    // The 0x2c0 byte object at +0x10 (the constructor 0x710107b63c): three tables of pointers with
    // a count in front of each one.
    struct Data {
        u8 _0[0x290];
        /* 0x290 */ u32 mCount0;
        u32 _294;
        /* 0x298 */ void** mTable0;
        /* 0x2a0 */ u32 mCount1;
        u32 _2a4;
        /* 0x2a8 */ void** mTable1;
        /* 0x2b0 */ u32 mCount2;
        u32 _2b4;
        /* 0x2b8 */ void** mTable2;
    };

    // 0x710107c9c4: the entry of the first table (at most 64 entries).
    void* sub_710107C9C4(s32 index);
    // 0x710107c9f4: the entry of the second table (at most 32 entries).
    void* sub_710107C9F4(s32 index);
    // 0x710107ca24: the entry of the third table (at most 32 entries).
    void* sub_710107CA24(s32 index);

    // The vtable pointer of the original class (0x71025041b8). The class is not polymorphic here,
    // so the slot is kept as plain data to keep the member offsets right.
    u64 _0 = 0;
    /* 0x08 */ const gsys::ModelSceneEnv* mEnv = nullptr;
    /* 0x10 */ Data* mData = nullptr;
    u8 _18[0x58 - 0x18];
};
KSYS_CHECK_SIZE_NX150(AreaEnvGetter, 0x58);

}  // namespace ksys::tera
