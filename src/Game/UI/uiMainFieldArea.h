#pragma once

#include <container/seadObjList.h>
#include <prim/seadSafeString.h>

namespace uking::ui {

// Main-field area parser A72218..A724B4 fills each record from a map tile name.
// Names are descriptive; index = column + 12 * row.
struct MainFieldAreaTile {
    // ObjList::clear at 9AF714..9AF744 resets the record before returning its pool slot.
    ~MainFieldAreaTile() {
        mName = sead::SafeString();
        mIndex = -1;
        mColumn = -1;
        mRow = -1;
    }

    /* 0x00 */ sead::SafeString mName;
    /* 0x10 */ s32 mIndex = -1;
    /* 0x14 */ s32 mColumn = -1;
    /* 0x18 */ s32 mRow = -1;
};
static_assert(sizeof(MainFieldAreaTile) == 0x20);

// A72108..A721B4 constructs 25 slots of stride 0x30, including each internal list node.
using MainFieldArea = sead::FixedObjList<MainFieldAreaTile, 25>;
static_assert(sizeof(MainFieldArea) == 0x4e0);

}  // namespace uking::ui
