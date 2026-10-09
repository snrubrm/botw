#include "Game/UI/uiScreens.h"
#include <limits>
#include "Game/UI/euiBoxCursor.h"
#include "Game/UI/euiButton.h"
#include "Game/UI/euiPartsEx.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiUtils.h"

namespace uking::ui {

// Initialized as two FLT_MAX components by native 9384e4; read as the
// optional layout size by 93bb48 and copied by both parameter lifetime bodies.
sead::Vector2f sUnk_71025D5CE8{std::numeric_limits<f32>::max(), std::numeric_limits<f32>::max()};

// 0x7100938c94
// NON_MATCHING: Vector2 component copies and global addressing differ.
ScreenAppPictureBookEntry::Params::Params() {
    _28.clear();
    _80.clear();
    _d8.clear();
    _130.format("N_PartsSize_00");
    _188.clear();
    _1e0.clear();
    _238 = 0;
    _240.clear();
    _298 = 3;
    _29c = 0;
    _2a0 = 1;
    _2a4 = 1;
    _2a8 = sUnk_71025D5CE8;
    _2c8 = false;
    _2c9 = false;
    _2ca = true;
    _2cb = true;
    _2b0 = sead::Vector2f::zero;
    _2b8 = sead::Vector2f::zero;
    _2c0 = sead::Vector2f::zero;
    _2cc = false;
    _2cd = true;
    _2d0 = nullptr;
}

// 0x7100938e9c
// NON_MATCHING: Vector2 component copies and global addressing differ.
ScreenAppPictureBookEntry::Params::~Params() {
    _28.clear();
    _80.clear();
    _d8.clear();
    _130.clear();
    _188.clear();
    _1e0.clear();
    _238 = 0;
    _240.clear();
    _298 = 0;
    _29c = -1;
    _2a0 = -1;
    _2a4 = -1;
    _2a8 = sUnk_71025D5CE8;
    _2b0 = sead::Vector2f::zero;
    _2b8 = sead::Vector2f::zero;
    _2c0 = sead::Vector2f::zero;
    _2d0 = nullptr;
    _2cc = false;
    _2cd = false;
    _2c8 = false;
    _2c9 = false;
    _2ca = false;
    _2cb = false;
}

// 0x710093a13c / 0x710093a238
// NON_MATCHING: D1 has Vector2 component-copy differences; D0 retains a D1 call
// rather than inlining the lifetime body and dropping dead parameter resets.
ScreenAppPictureBookEntry::~ScreenAppPictureBookEntry() {
    if (mIconControl) {
        delete mIconControl;
        mIconControl = nullptr;
    }
    if (mPageControl) {
        delete mPageControl;
        mPageControl = nullptr;
    }
    if (mGuideControl) {
        delete mGuideControl;
        mGuideControl = nullptr;
    }
}

// NON_MATCHING: empty-string comparison loads and page-count branches are scheduled differently.
// 0x710093ac7c
void ScreenAppPictureBookEntry::sub_710093AC7C() {
    sub_710093BB48();
    sub_710093BDFC();
    if (mParams._d8.isEmpty()) {
        _2f4 = mParams._29c;
    } else if (mParams._29c == 0) {
        _2f4 = 0;
    } else {
        const s32 count = mParams._2a0 * mParams._2a4;
        _2f4 = mParams._29c < count ? 1 : sead::Mathf::ceil(f32(mParams._29c) / f32(count));
    }
    sub_710093C040();
    if (mIconControl)
        mIconControl->sub_7100988010(mParams._238);
    if (mPageControl)
        mPageControl->sub_7100936A28(_2f4);
    if (mGuideControl)
        mGuideControl->sub_7100936BCC(mController->_40[2], mController->_40[3]);
}

// 0x710093a500
void ScreenAppPictureBookEntry::sub_710093A500(sead::Heap* heap) {
    const s32 count = mParams._298;
    if (count > 0) {
        mRecords.allocBuffer(count, heap, 8);
        for (s32 i = 0; i < count; ++i)
            mRecords.pushBack(new (heap, 8) PictureBookGroupRecord{0, sead::Vector2f::zero, -1});
    }
    sub_710093A5C0(heap);
    sub_710093A758();
    sub_710093AC7C();
}

// 0x710093a5c0
void ScreenAppPictureBookEntry::sub_710093A5C0(sead::Heap* heap) {
    eui::LayoutEx* page = nullptr;
    eui::LayoutEx* guide = nullptr;
    if (!mParams._188.isEmpty()) {
        auto* button = nn::font::DynamicCast<eui::UniteButton>(
            mController->mScreen->sub_7100A480B4(mParams._188));
        if (button) {
            mIconControl = new (heap, 8) Unk_7102477468;
            if (mIconControl)
                mIconControl->sub_7100987FBC(button);
            page = button->mLayout->findPartsLayout("Pa_Scroll_00");
            guide = button->mLayout->findPartsLayout("Pa_Rstick_00");
        }
    }
    if (!mParams._1e0.isEmpty()) {
        // Native93A6C8..D0 treats this optional named pane as Parts and uses
        // its established layout link at +f0, without a runtime type test.
        auto* parts = static_cast<nn::ui2d::Parts*>(
            mController->mScreen->sub_7100A48104(mParams._1e0, nullptr));
        if (parts)
            page = static_cast<eui::LayoutEx*>(parts->mPartsLayoutLink.layout);
    }
    if (page) {
        mPageControl = new (heap, 8) Unk_7102474c28;
        if (mPageControl)
            mPageControl->sub_7100936998(page);
    }
    if (guide) {
        mGuideControl = new (heap, 8) Unk_7102474c48;
        if (mGuideControl)
            mGuideControl->sub_7100936B18(guide);
    }
}

// 0x7100939f68 (D1) / 0x7100939fb8 (D0)
Unk_7102474f10::~Unk_7102474f10() {
    _8 = nullptr;
    mEntry = nullptr;
    mController = nullptr;
    mUnits.clear();
    _30 = nullptr;
    mRecord = nullptr;
    delete _40;
    _40 = nullptr;
}

// 0x710093e428
u32 ScreenAppPictureBookUnk::sub_710093E428(s32 index) {
    return sub_710093E784(index);
}

// NON_MATCHING: only the order of the two loop initialisers (`mov w9, wzr` before `mov x10, xzr` in the original)
// 0x710093e900
u32 ScreenAppPictureBookUnk::sub_710093E900(s32 base, s32 count) {
    s32 sum = 0;
    if (!_290)
        return sub_710093E784(0);
    for (s32 i = 0; i < count; ++i) {
        if (_288 > static_cast<u64>(i) && _290[i])
            sum += _290[i]->mParams._29c;
    }
    return sub_710093E784(sum + base);
}

// 0x710093f10c
void ScreenAppPictureBookUnk::sub_710093F10C(s32 index, s32* out_index, s32* out_value) {
    if (!_290)
        return;
    const s32 count = static_cast<s32>(_288);
    if (count == 0)
        return;
    ScreenAppPictureBookEntry** end = _290 + count;
    for (ScreenAppPictureBookEntry** p = _290; p != end; ++p) {
        ScreenAppPictureBookEntry* entry = *p;
        if (entry) {
            const s32 rest = index - entry->mParams._29c;
            if (rest < 0) {
                *out_value = entry->_2f0;
                *out_index = index;
                return;
            }
            index = rest;
        }
    }
}

// 0x710093a008
void Unk_7102474f10::sub_710093A008(s32 mode) {
    switch (mode) {
    case 3:
        if (_30)
            _30->PlayFromCurrent(eui::Animator::PlayType(0), 1.0f);
        else if (_8)
            _8->sub_7100BDDE7C(false, 0, true);
        break;
    case 4:
        if (_30)
            _30->PlayAuto(1.0f);
        else if (_8)
            _8->sub_7100BDDE7C(false, 0, true);
        break;
    case 5:
        if (_30)
            _30->StopAtMax();
        else if (_8)
            _8->sub_7100BDDE7C(false, 1, true);
        break;
    }
}

// 0x710093a0a8
void Unk_7102474f10::sub_710093A0A8(s32 mode) {
    switch (mode) {
    case 0:
        if (_30)
            _30->PlayFromCurrent(eui::Animator::PlayType(0), -1.0f);
        else if (_8)
            _8->startAnimCloseImpl_(false, false);
        break;
    case 1:
        if (_30)
            _30->PlayAuto(-1.0f);
        else if (_8)
            _8->startAnimCloseImpl_(false, false);
        break;
    case 2:
        if (_30)
            _30->StopAtMin();
        else if (_8)
            _8->startAnimCloseImpl_(false, true);
        break;
    }
}

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
                                          ((flags & 1) || entry->mParams._2ca) && !entry->_38c &&
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
    s32 span = entry->mParams._2a0;
    s32 start = l->_3c;
    s32 step = entry->mParams._2a4;
    s32 limit = entry->_2f0;
    s32 total = start + base * span * step;
    u64 i = 0;
    s32 sum = 0;
    if (limit >= 1) {
        for (; i != limit; ++i) {
            if (_288 > i) {
                if (ScreenAppPictureBookEntry* e = _290[i])
                    sum += e->mParams._29c;
            }
        }
    }
    return total + sum;
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
                    if (e->mParams._29c > 0 && !e->_38c && !e->_38d) {
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
                    if (e->mParams._29c > 0 && !e->_38c && !e->_38d) {
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

// 0x710093f278
void ScreenAppPictureBookUnk::sub_710093F278(s32 value, s32 index) {
    if (_290 && static_cast<u32>(index) < _288) {
        ScreenAppPictureBookEntry* entry = _290[index];
        if (entry)
            entry->mParams._29c = value;
    }
    sub_710093F29C();
}

// 0x710093fd14
void ScreenAppPictureBookUnk::sub_710093FD14(s32 index) {
    if (index >= 0 && _290 && index < _2a8)
        _290[index]->_38c = true;
    sub_710093F7F8(_2c & 1);
    sub_710093F924(true);
}

// 0x710093fd6c
void ScreenAppPictureBookUnk::sub_710093FD6C() {
    for (s64 i = 0; i < _2a8; ++i)
        _290[i]->_38c = false;
    sub_710093F7F8(_2c & 1);
    sub_710093F924(true);
}

// 0x710093fdcc
void ScreenAppPictureBookUnk::sub_710093FDCC(s32 index) {
    if (index >= 0 && _290 && index < _2a8)
        _290[index]->_38d = true;
    sub_710093F29C();
    sub_710093F924(true);
}

// 0x710093fe1c
void ScreenAppPictureBookUnk::sub_710093FE1C() {
    for (s64 i = 0; i < _2a8; ++i)
        _290[i]->_38d = false;
    sub_710093F29C();
    sub_710093F924(true);
}

// 0x710093fe74
bool ScreenAppPictureBookUnk::sub_710093FE74(s32 index) const {
    if (index < 0 || index >= _2a8)
        return true;
    return _290[index]->_38d;
}

// 0x71009401e4
void ScreenAppPictureBookUnk::sub_71009401E4() {
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
            for (Unk_7102474e38& u : (*group)->mUnits) {
                eui::AnimButton* button = u._10;
                if (button && !(button->mFlags & 0x10))
                    button->ForceOff();
            }
        }
    }
}

// 0x7100940288
void ScreenAppPictureBookUnk::sub_7100940288() {
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
            for (Unk_7102474e38& u : (*group)->mUnits) {
                eui::AnimButton* button = u._10;
                if (button && button->IsDowning())
                    button->ForceOff();
            }
        }
    }
}

}  // namespace uking::ui
