#include "Game/UI/uiScreens.h"
#include "Game/UI/euiBoxCursor.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiUtils.h"

namespace uking::ui {

// 0x710093e784
// NON_MATCHING: loop lowering only (all loads/stores/calls/branches match, including the head,
// the clamps, the unit flag checks and the ScreenMgr/BoxCursorMgr tail). Three diffs remain: the
// original counts the pairwise _29c loop down (sub x9,x9,x11 then sub #2 with cbnz) while ours
// counts the negated trip count up (sub x9,x11,x9 then add #2); the second sum add has swapped
// operands (add w8,w11,w8 vs add w8,w8,w11); the _38d check sits in an out-of-line block while the
// original threads it inline after the _38c test.
u32 ScreenAppPictureBookUnk::sub_710093E784(s32 index) {
    if (index == -1) {
        _30c = -1;
        _310 = -1;
        return 0;
    }
    s32 total;
    u64 count = _288;
    if ((s32)count < 1) {
        total = -1;
    } else {
        ScreenAppPictureBookEntry** entries = _290;
        s32 sum;
        u64 step;
        if ((count & 1) != 0) {
            sum = entries[0]->_29c;
            step = 1;
        } else {
            sum = 0;
            step = 0;
        }
        if (count != 1) {
            entries += step;
            count -= step;
            entries += 1;
            do {
                sum = entries[-1]->_29c + sum;
                sum = entries[0]->_29c + sum;
                entries += 2;
                count -= 2;
            } while (count != 0);
        }
        total = sum - 1;
    }
    s32 t = total < index ? total : index;
    s32 cur = index < 0 ? 0 : t;
    _310 = cur;
    Unk_7102474e38* unit = sub_7100943684(index);
    eui::BoxCursorNode* node;
    if (unit == nullptr) {
        node = nullptr;
    } else {
        u32 flags = unit->_30;
        ScreenAppPictureBookEntry* entry = unit->_18->mEntry;
        if ((flags & 2) == 0 || ((flags & 1) == 0 && !entry->_2ca) || entry->_38c ||
            !entry->_38d) {
            _310 = _30c;
            return 0;
        }
        node = unit->_28;
    }
    if (cur != _30c)
        _320 = 0;
    if (node == nullptr) {
        eui::ScreenMgr* mgr = eui::ScreenMgr::instance();
        u32 size = mgr->getScreenCount();
        eui::Screen** screens = mgr->getScreenBuffer();
        eui::Screen** p = size > 0x44 ? screens + 0x44 : screens;
        eui::Screen* screen = *p;
        if (screen)
            screen->close(-4);
    } else {
        _30c = cur;
        eui::ScreenMgr* mgr = eui::ScreenMgr::instance();
        if (eui::BoxCursorMgr* boxmgr = mgr->getBoxCursorMgr())
            boxmgr->m5(node);
    }
    return 0;
}

}  // namespace uking::ui
