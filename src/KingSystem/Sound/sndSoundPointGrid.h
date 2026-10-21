#pragma once

#include <container/seadObjList.h>
#include <container/seadSafeArray.h>
#include <math/seadVector.h>
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}

namespace ksys::snd {

// Vtable 0x710251ad68 (no RTTI; 0xa48 bytes; Unk_SoundMgr38_10::_11c0, created by 0x71010317b4). Sorts the sound
// points of plants into the 3 x 3 placement map cells around the listener (_8b8 maps a cell to its list) and
// tracks the ones without a plant shake type.
class Unk_710251ad68 {
public:
    struct Item {
        u8 _0[0x10];
    };

    // Two sets of nine lists (one per cell) with up to 20 actors that are already handled.
    struct Lists {
        // 0x71012bfbf8: gives each list room for `num` items.
        void init(s32 num, sead::Heap* heap);

        /* 0x000 */ sead::SafeArray<sead::ObjList<Item>, 9> mLists;
        /* 0x1b0 */ void* mActors[20];
        /* 0x250 */ s32 mNumActors;
    };
    KSYS_CHECK_SIZE_NX150(Lists, 0x258);

    // One entry per point (0x400 bytes; constructor 0x71012c0d68, declared only).
    struct Points {
        Points();

        struct Point {
            sead::Vector3f pos;
            f32 distance;
        };
        Point mPoints[64];
    };
    KSYS_CHECK_SIZE_NX150(Points, 0x400);

    Unk_710251ad68();
    virtual ~Unk_710251ad68();

    // 0x71012bf9e4: frees the lists.
    void finalize();
    // 0x71012bfb84
    void init(sead::Heap* heap);
    // 0x71012c0c14: empties the lists and resets the cell map.
    void reset();

    /* 0x008 */ Lists _8;
    /* 0x260 */ Lists _260;
    /* 0x4b8 */ Points mPoints;
    /* 0x8b8 */ s32 mCellMap[9];
    /* 0x8dc */ sead::Vector2i mCell{sead::Vector2i(-0x80000000, -0x80000000)};
    /* 0x8e4 */ u32 _8e4 = 0;
    /* 0x8e8 */ u32 _8e8 = 0;
    /* 0x8ec */ u8 _8ec[4];
    /* 0x8f0 */ void* _8f0[40];
    /* 0xa30 */ s32 _a30;
    /* 0xa34 */ s32 mState = 0;
    /* 0xa38 */ u16 _a38 = 0;
    /* 0xa3a */ u8 _a3a = 0;
    /* 0xa3b */ u8 _a3b = 0;
    /* 0xa3c */ u8 _a3c = 0;
    /* 0xa40 */ f32 _a40 = 100.0f;
    /* 0xa44 */ f32 _a44 = 500.0f;
};
KSYS_CHECK_SIZE_NX150(Unk_710251ad68, 0xa48);

}  // namespace ksys::snd
