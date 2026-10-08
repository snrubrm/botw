#include "Game/UI/uiScreens.h"

namespace uking::ui {

// 0x710093f594
void ScreenAppPictureBookUnk::sub_710093F594(bool flag) {
    bool old = _2c & 1;
    if (!((old ^ flag) & 1))
        return;
    u32 flags = flag ? (_2c | 1) : (_2c & ~1u);
    _2c = flags;
    _38 = nullptr;
    if (flags & 1) {
        sub_710093F670();
    } else {
        if (PictureBookItem* item = _318) {
            if (item->_10) {
                item->_10 = false;
                item->m9();
            }
            _318 = nullptr;
        }
    }
    sub_710093F7F8(flag & 1);
    sub_710093F924(true);
    if (!flag) {
        ScreenEx* screen = mScreen;
        eui::BoxCursorNode* node = screen->mActiveCursorNode;
        if (node == nullptr)
            return;
        if (sub_710093FBF0(node) < 0)
            return;
        screen->mActiveCursorNode = nullptr;
        return;
    }
    if (old)
        return;
    sub_710093E784(_310);
}

// 0x710093f7f8
// NON_MATCHING: scheduling only (original uses an lsl+sub+cbnz byte-countdown while ours
// normalises to neg+add, and lowers the 7-operand flag expression to branches plus a cset
// while the original funnels all false paths to a shared mov w1,0 (all loads/stores/calls/
// branches match; the outer search loops and per-unit flag logic are structurally identical).
void ScreenAppPictureBookUnk::sub_710093F7F8(bool flag) {
    s64 count = _298;
    if (count == 0)
        return;
    PictureBookGroupList** outer = _2a0;
    PictureBookGroupList** end = outer + count;
    for (; outer != end; ++outer) {
        PictureBookGroupList* o = *outer;
        s64 n = o->_0;
        if (n == 0)
            continue;
        Unk_7102474f10** group = o->_8;
        Unk_7102474f10** gend = group + n;
        for (; group != gend; ++group) {
            Unk_7102474f10* g = *group;
            s64 k = g->mUnits.size();
            if (k == 0)
                continue;
            Unk_7102474e38** unit = g->mUnits.data();
            s64 left = k * 8;
            do {
                Unk_7102474e38* u = *unit;
                if (!flag) {
                    if (eui::AnimButton* button = u->_10)
                        button->setFlag10(false);
                } else {
                    eui::AnimButton* button = u->_10;
                    if (button) {
                        u32 flags = u->_30;
                        ScreenAppPictureBookUnk* ctrl = u->_20;
                        ScreenAppPictureBookEntry* entry = u->_18->mEntry;
                        button->setFlag10((flags & 4) && (ctrl->_2c & 1) &&
                                          ctrl->_340 == 2 && (flags & 2) &&
                                          ((flags & 1) || entry->_2ca) && !entry->_38c &&
                                          entry->_38d == 0);
                    }
                }
                ++unit;
            } while ((left -= 8) != 0);
        }
    }
}

// 0x710093fbf0
// NON_MATCHING: regalloc/scheduling only (original keeps the leaf in x15 and the countdown in
// x14 with lsl+sub+cbnz while ours uses a named local (neg+add countdown) and different load/
// mul operand registers in the found-block; the _290-null path returns 0 via mov w0,wzr while
// the original returns the null pointer itself via mov w0,w8). All loads/stores/calls/branches
// match; the triple search loop, mul+madd index math and _29c sum loop are structurally identical.
s32 ScreenAppPictureBookUnk::sub_710093FBF0(eui::BoxCursorNode* node) {
    s32 result = -1;
    s64 count = _298;
    if (count == 0)
        return -1;
    Unk_7102474e38* l = nullptr;
    PictureBookGroupList** outer = _2a0;
    PictureBookGroupList** end = outer + count;
    for (; outer != end; ++outer) {
        PictureBookGroupList* o = *outer;
        s64 n = o->_0;
        if (n == 0)
            continue;
        Unk_7102474f10** group = o->_8;
        Unk_7102474f10** gend = group + n;
        for (; group != gend; ++group) {
            Unk_7102474f10* g = *group;
            if (g->mEntry == nullptr)
                continue;
            if (g->mRecord == nullptr)
                continue;
            if (g->mRecord->_c < 0)
                continue;
            s64 k = g->mUnits.size();
            if (k == 0)
                continue;
            Unk_7102474e38** unit = g->mUnits.data();
            s64 left = k * 8;
            do {
                l = *unit;
                if ((l->_30 & 4) != 0 && l->_28 == node)
                    goto found;
                ++unit;
            } while ((left -= 8) != 0);
        }
    }
    return result;
found:
    if (_290 == nullptr)
        return 0;
    Unk_7102474f10* group = l->_18;
    PictureBookGroupRecord* record = group->mRecord;
    ScreenAppPictureBookEntry* entry = group->mEntry;
    s32 base = record->_c;
    s32 span = entry->_2a0;
    s32 start = l->_3c;
    s32 step = entry->_2a4;
    s32 limit = entry->_2f0;
    s32 total = start + base * span * step;
    u64 i = 0;
    s32 sum = 0;
    if (limit >= 1) {
        for (; i != limit; ++i) {
            if (_288 > i) {
                if (ScreenAppPictureBookEntry* e = _290[i])
                    sum += e->_29c;
            }
        }
    }
    return total + sum;
}

// 0x710093dad4
void ScreenAppPictureBookUnk::sub_710093DAD4(s32 value) {
    if (_33c <= value)
        _33c = value;
}

// 0x710093dae8
void ScreenAppPictureBookUnk::sub_710093DAE8(s32 value) {
    if (_33c <= value)
        _33c = value;
}

// 0x7100939f58
bool ScreenAppPictureBookUnk::sub_7100939F58() const {
    return _340 == 2;
}

// 0x710093fe74
bool ScreenAppPictureBookUnk::sub_710093FE74(s32 index) const {
    if (index < 0 || index >= _2a8)
        return true;
    return _290[index]->_38d;
}

}  // namespace uking::ui
