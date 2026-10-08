#include "Game/UI/uiScreens.h"
#include "Game/UI/euiBoxCursor.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiUtils.h"

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

// 0x710093f670
// NON_MATCHING: lowering only (all loads/stores/calls/branches match, including both loop
// skeletons with their reloads, the record/match logic and the select/deselect truth table).
// Four small diffs remain: _2e4 is loaded before _288 (ours loads them in compare order); the
// else-path null check is mov+cmp+beq while ours uses cbz; the select block loads _318 after the
// _10 store while ours loads it before; (all scheduling/codegen-shape, no semantic difference).
void ScreenAppPictureBookUnk::sub_710093F670() {
    if ((_2c & 1) == 0)
        return;
    u32 n = _298;
    if ((s32)n < 1)
        return;
    u64 count298 = n;
    u32 lim = n;
    u64 i = 0;
    while (true) {
        if (lim > i) {
            PictureBookGroupList* group = _2a0[i];
            if (group && group->_0 >= 1) {
                u32 count = group->_0;
                u64 last = (u64)count - 1;
                u64 j = 0;
                while (true) {
                    if (count > j) {
                        Unk_7102474f10* g = group->_8[j];
                        if (g) {
                            ScreenAppPictureBookEntry* entry = g->mEntry;
                            s32 rb = -1;
                            if (PictureBookGroupRecord* record = g->mRecord)
                                rb = record->_c;
                            bool sel;
                            if (_288 > _2e4) {
                                if (_290[_2e4] != entry)
                                    sel = false;
                                else
                                    sel = _2ec == rb;
                            } else {
                                if (entry != nullptr)
                                    sel = false;
                                else
                                    sel = _2ec == rb;
                            }
                            if (PictureBookItem* item = g->_40) {
                                bool old = item->_10;
                                if (!old && sel) {
                                    item->_10 = true;
                                    item->m8(_318);
                                    _318 = item;
                                }
                                if (old && !sel) {
                                    item->_10 = false;
                                    item->m9();
                                }
                            }
                        }
                    }
                    if (last != j) {
                        count = group->_0;
                        ++j;
                        continue;
                    }
                    break;
                }
            }
        }
        ++i;
        if (i != count298) {
            lim = _298;
            continue;
        }
        break;
    }
}

// 0x710093f7f8
// NON_MATCHING: the 7-operand flag expression is lowered to branches plus a cset, while the original
// funnels all false paths to a shared mov w1,0; registers differ in that block.
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
            for (Unk_7102474e38& u : g->mUnits) {
                if (!flag) {
                    if (eui::AnimButton* button = u._10)
                        button->setFlag10(false);
                } else {
                    eui::AnimButton* button = u._10;
                    if (button) {
                        u32 flags = u._30;
                        ScreenAppPictureBookUnk* ctrl = u._20;
                        ScreenAppPictureBookEntry* entry = u._18->mEntry;
                        button->setFlag10((flags & 4) && (ctrl->_2c & 1) &&
                                          ctrl->_340 == 2 && (flags & 2) &&
                                          ((flags & 1) || entry->_2ca) && !entry->_38c &&
                                          entry->_38d == 0);
                    }
                }
            }
        }
    }
}

// 0x710093fbf0
// NON_MATCHING: regalloc in the found block (load/mul operand registers), and the _290-null path returns 0
// via mov w0,wzr while the original returns the null pointer itself via mov w0,w8.
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
            for (Unk_7102474e38& unit : g->mUnits) {
                if ((unit._30 & 4) != 0 && unit._28 == node) {
                    l = &unit;
                    goto found;
                }
            }
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

// File-static rodata tables for sub_710093F924 (values verified against the original with fstr;
// our addresses differ from the original's file-local ones, so the adrp/add pairs cannot match
// and the function caps at m).
namespace {
const u32 sUnk_7101E794A8[4] = {2, 1, 8, 4};
const u32 sUnk_7101E794B8[4] = {1, 2, 4, 8};
const s64 sUnk_7101E79C80[4] = {1, 0, 3, 2};
}  // namespace

// 0x710093f924
// NON_MATCHING: data addressing plus search-layout lowering (all table values verified against the
// original, but the three file-static tables live at different addresses so every adrp/add pair
// differs; the backward-search block sits inline while the original outlines it, with knock-on
// register allocation through the search; the entry loops, the _30 updates, the layout null checks
// and the whole animation tail match).
void ScreenAppPictureBookUnk::sub_710093F924(bool flag) {
    if (!flag && (_28 & 0x30) == 0)
        return;
    s64 c = _c8;
    _30 = 0;
    eui::LayoutEx* layout_a;
    eui::LayoutEx* layout_b;
    u32 mask_b;
    u32 mask_a;
    if ((u32)c <= 3) {
        s64 idx = sUnk_7101E79C80[c];
        mask_a = sUnk_7101E794A8[c];
        mask_b = sUnk_7101E794B8[c];
        layout_a = _40[idx];
        layout_b = _40[(u32)c];
    } else {
        layout_a = nullptr;
        layout_b = nullptr;
        mask_b = 8;
        mask_a = 4;
    }
    u32 bits;
    if ((_2c & 1) == 0) {
        bits = 0;
        _30 = 0;
        _30 = bits & ~mask_b;
    } else {
        bits = mask_a;
        _30 = mask_a;
        if (_2f0 <= 0) {
            bool found_back = false;
            if (_2e8 >= 1) {
                s64 i = (s64)_2e8 - 1;
                while (true) {
                    ScreenAppPictureBookEntry* e = _290[i];
                    if (e->_29c > 0 && !e->_38c && !e->_38d) {
                        found_back = true;
                        break;
                    }
                    if (i < 1)
                        break;
                    --i;
                }
            }
            if (found_back) {
                bits = mask_a;
                _30 = mask_a;
            } else {
                bits = 0;
                _30 = 0;
            }
        }
        bool found_fwd = false;
        ScreenAppPictureBookEntry* entry = _290[_2e8];
        if (entry->_2f4 - 1 <= _2f0) {
            found_fwd = true;
        } else {
            s64 last = (s64)_288 - 1;
            if ((s32)_2e8 < (s32)last) {
                s64 i = _2e8;
                while (true) {
                    ScreenAppPictureBookEntry* e = _290[i + 1];
                    if (e->_29c > 0 && !e->_38c && !e->_38d) {
                        found_fwd = true;
                        break;
                    }
                    ++i;
                    if (i >= last)
                        break;
                }
            }
        }
        if (found_fwd)
            _30 = bits | mask_b;
        else
            _30 = bits & ~mask_b;
    }
    if (!layout_a)
        return;
    if (!layout_b)
        return;
    if (flag) {
        if ((_30 & mask_a) == 0)
            layout_a->startAnimCloseImpl_(false, true);
        else
            layout_a->sub_7100BDDE7C(false, 1, true);
        if ((_30 & mask_b) == 0) {
            layout_b->startAnimCloseImpl_(false, true);
            return;
        }
        layout_b->sub_7100BDDE7C(false, 1, true);
    } else {
        if ((_30 & mask_a) == 0) {
            layout_a->startAnimCloseImpl_(false, false);
        } else if (layout_b->_91 - 1u < 2u) {
            sub_7100AA1D5C(layout_a, layout_b, true);
        } else {
            layout_a->sub_7100BDDE7C(false, 0, true);
        }
        if ((_30 & mask_b) == 0) {
            layout_b->startAnimCloseImpl_(false, false);
            return;
        }
        if (layout_a->_91 - 1u < 2u) {
            sub_7100AA1D5C(layout_b, layout_a, true);
            return;
        }
        layout_b->sub_7100BDDE7C(false, 0, true);
    }
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
