#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "Game/UI/uiTUStatics.h"


namespace uking::ui {

// Per-group element counts of the staff roll text blocks. This is the ScreenStaffRoll TU's merged
// static block (initialized by 0x7100a5b124, base 0x71025f54d0): the group Buffer sits at +0x188 and
// its records at +0x1e8, 0x18 bytes each.
struct StaffRollGroup {
    s32 count;
    u8 _4[0x14];
};
static StaffRollGroup sStaffRollGroups[5] = {{1}, {31}, {31}, {31}, {1}};
static struct StaffRollGroupTable {
    u8 _0[0x188];
    sead::Buffer<StaffRollGroup> groups;
} sStaffRollGroupTable = {{}, {5, sStaffRollGroups}};

// 0x7100a5d9b8
// NON_MATCHING: popBack's size store and buffer load are scheduled in the opposite order (one instruction).
ScreenStaffRoll::~ScreenStaffRoll() {
    for (s32 i = 0; i < 1000; ++i) {
        Unk_71024993a0* entry = mEntries.popBack();
        if (!entry)
            break;
        delete entry;
    }
    mEntries.freeBuffer();

    for (s32 i = 0; i < 5; ++i) {
        const s32 count = sStaffRollGroupTable.groups[i].count;
        for (s32 j = 0; j < count; ++j) {
            Unk_710249a1a0* block = mTextBlocks[i].popBack();
            if (!block)
                break;
            delete block;
        }
        mTextBlocks[i].freeBuffer();
    }
}

}  // namespace uking::ui
