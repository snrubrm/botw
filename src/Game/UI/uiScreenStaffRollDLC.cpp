#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "Game/UI/uiTUStatics.h"


namespace uking::ui {

// The TU's statics (static initializer 0x7100a56e60), merged into the block at 0x71025f4030 after
// the uiTUStatics.h objects. sub_7100A58480 passes the 5400 duration to ksys::Timer::hasEnded.
struct StaffRollDlcStatics {
    u8 _0[0x18];
    f32 mDuration;
};
KSYS_VISIBILITY_HIDDEN StaffRollDlcStatics sUnk_71025F4030 = {{}, 5399.9995f};
static sead::SafeString sMessageSet = "LayoutMsg/StaffRollDLC_00";
static sead::SafeString sStaticSet = "StaticMsg/StaffRollDLC";

// Per-group element counts of the staff roll text blocks (the original's merged static block, at
// +0x188/+0x190 of the block at 0x71025f4030; the records live at +0x1e8 and are 0x18 bytes each).
// Only the counts are read by the destructor; the names are used by the entry builder.
struct StaffRollGroup {
    s32 count;
    u8 _4[0x14];
};
static StaffRollGroup sStaffRollGroups[5] = {{1}, {31}, {31}, {31}, {1}};
static struct StaffRollGroupTable {
    u8 _0[0x188];
    sead::Buffer<StaffRollGroup> groups;
} sStaffRollGroupTable = {{}, {5, sStaffRollGroups}};

// 0x7100a58284
// NON_MATCHING: popBack's size store and buffer load are scheduled in the opposite order (one instruction).
ScreenStaffRollDLC::~ScreenStaffRollDLC() {
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

// 0x7100a58480
// NON_MATCHING: the original reads the 5400 duration from the TU's merged static block; our
// clang folds the constant-file static binding to a literal-pool load.
void ScreenStaffRollDLC::m94() {
    if (!isOpened() || _270 > 0.0f)
        return;
    if (!_3610.hasEnded(sUnk_71025F4030.mDuration))
        _3610.update();
    sub_7100A58508(_3700, -_3688.y);
    sub_7100A58778(_3704);
    sub_7100A588EC();
}

}  // namespace uking::ui
