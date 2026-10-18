#pragma once

#include <container/seadObjList.h>
#include <prim/seadSafeString.h>
#include "KingSystem/GameData/gdtFlagHandle.h"

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

    // inline-only in the original; names are guesses. The name/grid population repeats
    // in both area and subarea parsing at A72278..A724B4 and A72CC0..A72EF4.
    void setName(const sead::SafeString& name) {
        mName = name;
        mIndex = parseColumn(name) + 12 * parseRow(name);
        mColumn = parseColumn(name);
        mRow = parseRow(name);
    }
    static s32 parseColumn(const sead::SafeString& name) {
        const char column = name[0];
        if (column == 'Z')
            return 0;
        return u32(column - 'A') < 12 ? column - '@' : -1;
    }
    static s32 parseRow(const sead::SafeString& name) {
        const char row = name[2];
        return u32(row - '0') < 10 ? row - '0' : -1;
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

// A72520 resets the mask after list erasure, before returning its slot to the free pool.
struct MainFieldAreaMask {
    ~MainFieldAreaMask() { mMask = 0; }
    u16 mMask = 0;
};
static_assert(sizeof(MainFieldAreaMask) == 2);
using MainFieldAreaMasks = sead::FixedObjList<MainFieldAreaMask, 120>;
static_assert(sizeof(MainFieldAreaMasks) == 0xb70);

// A72974..A729B4 resets the name and flag handle at the item destructor position.
struct MainFieldSubArea {
    ~MainFieldSubArea() {
        mFlagName = sead::SafeString();
        mFlagHandle = ksys::gdt::InvalidHandle;
    }
    /* 0x00 */ sead::SafeString mFlagName;
    /* 0x10 */ ksys::gdt::FlagHandle mFlagHandle = ksys::gdt::InvalidHandle;
    /* 0x18 */ sead::FixedObjList<MainFieldAreaTile, 4> mTargets;
};
static_assert(sizeof(MainFieldSubArea) == 0x108);
using MainFieldSubAreas = sead::FixedObjList<MainFieldSubArea, 10>;
static_assert(sizeof(MainFieldSubAreas) == 0xb20);

// A72F54 resets both halves at the item destructor position.
struct MainFieldSubMask {
    ~MainFieldSubMask() {
        mFilter = 0;
        mSubMask = 0;
    }
    u16 mFilter = 0;
    u16 mSubMask = 0;
};
static_assert(sizeof(MainFieldSubMask) == 4);
using MainFieldSubMasks = sead::FixedObjList<MainFieldSubMask, 120>;
static_assert(sizeof(MainFieldSubMasks) == 0xb70);

}  // namespace uking::ui
