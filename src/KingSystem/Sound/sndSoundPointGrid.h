#pragma once

#include <container/seadObjList.h>
#include <container/seadSafeArray.h>
#include <prim/seadEnum.h>
#include <math/seadMathCalcCommon.h>
#include <math/seadVector.h>
#include "KingSystem/Utils/Types.h"

namespace aal {
class Listener;
}

namespace sead {
class Heap;
}

namespace ksys::map {
class PlacementMgr;
struct Unk_71012497f8Entry;
}

namespace ksys::snd {

// Vtable 0x710251ad68 (no RTTI; 0xa48 bytes; Unk_SoundMgr38_10::_11c0, created by 0x71010317b4). Sorts the sound
// points of plants into the 3 x 3 placement map cells around the listener (_8b8 maps a cell to its list) and
// tracks the ones without a plant shake type.
class Unk_710251ad68 {
public:
    // The sound type of a plant (the text "cBush , cGrass" is in the binary; the name is a guess from the debug
    // string "[SoundType : %s]" next to it). It selects one of the two list sets.
    // clang-format off
    SEAD_ENUM(SoundType, cBush , cGrass)
    // clang-format on

    // Two sets of nine lists of sound point positions (one list per map cell) and up to 20 actors that are
    // already handled.
    struct Lists {
        // 0x71012bfbf8: gives each list room for `num` positions.
        void init(s32 num, sead::Heap* heap);

        /* 0x000 */ sead::SafeArray<sead::ObjList<sead::Vector3f>, 9> mLists;
        /* 0x1b0 */ void* mActors[20];
        /* 0x250 */ s32 mNumActors;
    };
    KSYS_CHECK_SIZE_NX150(Lists, 0x258);

    // The nearest point in each of 32 directions around the listener.
    struct Point {
        sead::Vector3f pos{sead::Vector3f::zero};
        f32 distance = sead::Mathf::maxNumber();
    };

    Unk_710251ad68();
    virtual ~Unk_710251ad68();

    // 0x71012bf9e4: frees the lists.
    void finalize();
    // 0x71012bfb84
    void init(sead::Heap* heap);
    // 0x71012c0c14: empties the lists and resets the cell map.
    void reset();
    // 0x71012c0034: moves the lists with the listener's map cell (each list keeps its cell, new cells get the
    // lists of the cells that were left), then fills the list of one sub-cell around the listener (one per call).
    void updateCells(map::PlacementMgr* mgr, const aal::Listener* listener);
    // 0x71012c0898: the PlacementMgr query callback; sorts the sound point of a plant into the list of its kind
    // (bush or grass) for the current cell.
    bool sub_71012C0898(map::Unk_71012497f8Entry* entry);
    // 0x71012c06d0: finds the nearest point of each set in each direction around the listener.
    void updatePoints(const aal::Listener* listener);

    /* 0x008 */ Lists mLists[2];
    // Constructed by 0x71012c0d68 (not inlined).
    /* 0x4b8 */ sead::SafeArray<sead::SafeArray<Point, 32>, 2> mPoints;
    /* 0x8b8 */ s32 mCellMap[9];
    /* 0x8dc */ sead::Vector2i mCell{sead::Vector2i(-0x80000000, -0x80000000)};
    // The sub-cell that the next updateCells call fills (an index into the offsets 0x7101ec76f8).
    /* 0x8e4 */ s32 _8e4 = 0;
    // The list (cell) that new points go to.
    /* 0x8e8 */ s32 _8e8 = 0;
    /* 0x8ec */ u8 _8ec[4];
    // Actors without a plant shake type.
    /* 0x8f0 */ void* _8f0[40];
    /* 0xa30 */ s32 _a30;
    /* 0xa34 */ s32 mState = 0;
    /* 0xa38 */ u8 _a38 = 0;
    // Enables the debug drawing of the lists.
    /* 0xa39 */ bool _a39 = false;
    /* 0xa3a */ u8 _a3a = 0;
    /* 0xa3b */ u8 _a3b = 0;
    /* 0xa3c */ u8 _a3c = 0;
    /* 0xa40 */ f32 _a40 = 100.0f;
    /* 0xa44 */ f32 _a44 = 500.0f;
};
KSYS_CHECK_SIZE_NX150(Unk_710251ad68, 0xa48);

}  // namespace ksys::snd
