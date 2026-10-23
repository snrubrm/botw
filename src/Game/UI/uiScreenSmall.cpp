#include "Game/UI/euiBoxCursor.h"
#include "Game/UI/euiTraceGaugeControl.h"
#include "Game/UI/uiScreenControlCreators.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiAlignPane.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUnkTiny.h"
#include "Game/UI/uiScreenChildStates.h"
#include <container/seadBuffer.h>
#include "Game/UI/uiUtils.h"
#include "Game/UI/uiOnUiActorMgr.h"
#include "Game/UI/uiManager.h"
#include "Game/UI/uiUnk_7102506d38.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "Game/UI/uiUI.h"
#include "Game/gameSaveSystem.h"
#include <gfx/seadGraphics.h>
#include "Game/UI/euiPartsEx.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Event/evtEvent.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"
#include <math/seadMathCalcCommon.h>
#include "Game/UI/uiTUStatics.h"

// Small leaf screen methods (named after their CSV address).
namespace uking::ui {

PouchCategory sub_7100A82D08(s32 tab);

// NON_MATCHING: the compiler outlines the SafeArray member constructor.
Unk_7100A341D0::Unk_7100A341D0() = default;
// NON_MATCHING: the compiler outlines the SafeArray member destructor.
Unk_7100A341D0::~Unk_7100A341D0() = default;

// 0x7100a34a28
void ScreenPauseMenu::sub_7100A34A28() {
    if (isOpened() && !_3642)
        invokeSoundLink2Event_("mc_Close");
    sub_7100A3471C();
    _3642 = false;
}

// NON_MATCHING: register allocation (the category entry pointer and the layout-pair counters) and the
// pane call / layouts pointer order differ; the logic matches.
// 0x7100a38fe8
bool ScreenPauseMenu::sub_7100A38FE8(u8 category, bool a2) {
    if (_3bf8 == 2)
        return false;

    auto* entry = _3a00[category < 3 ? category : 0];
    const s32 id = entry->_130;
    if (s32(sub_7100A82D08(id)) > 2)
        return false;

    for (s32 i = 0; i < 0x14; ++i) {
        bool valid = false;
        const s32 value = entry->_c78[i];
        if (value >= 0) {
            PouchItem* item = mPauseMenuDataMgr->__auto8(id, value);
            if (item && item->isInInventory()) {
                bool ok;
                if (_3bf8 == 1)
                    ok = sub_7100AA6D54(item->getName());
                else if (_3bf8 == 0)
                    ok = sub_7100AA6C84(item->getName());
                else
                    ok = false;
                if (ok)
                    valid = true;
            }
        }

        if (!valid) {
            _3be8[i].sub_7100932FDC(_3bf8, a2);
            continue;
        }

        if (entry) {
            auto* pane = entry->mButtons[i].mBreakNewController.sub_71009B170C();
            _3be8[i].sub_710093307C(_3bf8, pane);
        }

        eui::LayoutEx* layout = nullptr;
        for (s32 j = 0; j < 0x14; ++j) {
            if (j == i)
                continue;
            if (_3be8[j].sub_7100933038(_3bf8)) {
                layout = _3be8[j].sub_7100932F7C(_3bf8);
                break;
            }
        }
        _3be8[i].sub_7100932FA8(_3bf8, layout, a2);
    }
    return true;
}

// 0x7100a391cc
void ScreenPauseMenu::sub_7100A391CC(bool a1) {
    if (_3640)
        return;
    _3640 = true;
    _3620 = mSelectedCategory;
    sub_7100A392D8();
    if (auto* info = sead::DynamicCast<ScreenPauseMenuInfo>(
            eui::ScreenMgr::instance()->getScreen(ScreenId::PauseMenuInfo))) {
        info->sub_7100A300AC();
        info->sub_7100A30380(0);
        if (a1)
            info->sub_7100A30DF0(true);
    }
    if (auto* mgr = OnUiActorMgr::instance())
        mgr->sub_71009079EC(true);
}

// 0x7100a392d8
// NON_MATCHING: the two _3620 reads inside the else are hoisted before the two sub_7100A82D08
// calls here (the original reloads the second one after them), and the dir checks take branches
// instead of the original's two if-converted ands.
void ScreenPauseMenu::sub_7100A392D8() {
    if (!mFirstGuideLayout || !mSecondGuideLayout)
        return;

    const s32 dir = _3674 == 0 ? _3644 : _3648;
    bool show_first;
    bool show_second;
    if (_3620 == -1) {
        if (dir >= 1)
            show_first = _3624 >= dir && _3624 > 0;
        else
            show_first = false;
        if (dir >= -1)
            show_second = _3624 > dir + 1 && _3624 > 0;
        else
            show_second = false;
    } else {
        show_first = _3620 == s32(sub_7100A82D08(dir - 1));
        show_second = _3620 == s32(sub_7100A82D08(dir + 1));
    }

    if (show_first)
        sub_7100AA1D5C(mFirstGuideLayout, mSecondGuideLayout, true);
    else if (u8(mFirstGuideLayout->_91) - 1 < 2)
        mFirstGuideLayout->startAnimCloseImpl_(false, false);

    if (show_second)
        sub_7100AA1D5C(mSecondGuideLayout, mFirstGuideLayout, true);
    else if (u8(mSecondGuideLayout->_91) - 1 < 2)
        mSecondGuideLayout->startAnimCloseImpl_(false, false);

    if (mSelectedCategory == -1)
        return;
    const s32 idx = u32(mSelectedCategory) < 7 ? mSelectedCategory : 0;
    mTabControls.mEntries[idx].mGuide.sub_7100936BD4(show_first, show_second);
}

// 0x7101e78f64: the x offset of a tab control one page away / one page away in another category.
static const f32 sUnk_7101e78f64[2] = {505.0f, 490.0f};

// 0x7100a3772c (placeholder name): lays the three visible tab controls out around the current page.
// NON_MATCHING: the target's Unk_710247a028::sub_71009B01B4 call stays out of line there, but the
// class is defined in this TU here and gets inlined (which also drops the saved d8 and hoists the
// _3a18 load out of the loop).
void ScreenPauseMenu::sub_7100A3772C() {
    sub_7100AA9838();
    for (s32 i = -1; i < 2; ++i) {
        const u8 tab = wrapTab(s8(_3a18) + i);
        auto* control = _3a00[tab < 3 ? tab : 0];
        if (!control)
            continue;
        const s32 page = _3644 + i;
        if (!showTabPage(tab, page)) {
            control->sub_71009AFF68();
            _3a00[tab < 3 ? tab : 0]->sub_71009B020C(false);
            continue;
        }
        control->sub_71009B020C(true);
        if (tab == _3a18)
            continue;
        const f32 step = sUnk_7101e78f64[getTabIndex(_3644) == getTabIndex(page) ? 1 : 0];
        control->sub_71009B01C4(f32(i) * step +
                                _3a00[_3a18 < 3 ? _3a18 : 0]->sub_71009B01B4().x);
    }
    sub_7100A38FE8(_3a18, false);
    sub_7100AA9848();
}

// 0x7100a399f4 (placeholder name): enables the buttons of the last `_3628` items of tab `tab` when the
// sort flag changes.
// NON_MATCHING: the loop bound/index are 64-bit in the original (`ldrsw` + `cmp x21, x24`) and it keeps the
// `_3a00` element address in x25; ours keeps a 32-bit counter and loads the element once.
void ScreenPauseMenu::sub_7100A399F4(s32 a1, u8 tab) {
    const u8 old = _3641;
    _3641 = sub_7100AA7BAC(nullptr);
    if (_3641 == old)
        return;
    const s32 end = mTabControls.mEntries[1]._7c;
    const s32 start = sead::Mathi::max(end - _3628, 0);
    if (start >= end)
        return;
    auto* control = _3a00[tab < 3 ? tab : 0];
    for (s32 i = start; i < end; ++i) {
        control->sub_71009B04BC(i, _3641);
        bool enabled = false;
        if (!_3641)
            enabled = mPauseMenuDataMgr->x_24(a1, control->_c78[i < 20 ? i : 0]);
        control->sub_71009B04E0(i, enabled);
    }
}

// 0x7100a36784 (placeholder name): steps the page offset and re-lays the tab controls when the
// current page moved; then shows the page of the tab control that holds the target page.
// NON_MATCHING: the inlined wrapTab comparisons and the shared 2 constant differ per instance
// (ours compares the selected value, the original the sign-extended argument).
void ScreenPauseMenu::sub_7100A36784() {
    _3660 = 0;
    const f32 offset = _3650;
    if (!(offset >= -0.001f && offset <= 0.001f)) {
        const bool stepped = sub_7100AA2350(this, &_3650, 0.0f, 0.28f, 300.0f, 0.1f);
        const bool moved = sub_7100A3A920(offset - _3650);
        if (stepped || moved)
            _3648 = _3644;
    }
    if (!_3660 || !_3661)
        return;
    if (!sub_7100A3A7FC(_3648, _364c))
        return;
    _3661 = 0;
    const u8 tab = _3a18;
    const s32 page = _3648;
    u8 index;
    const u8 prev = wrapTab(u8(tab - 1));
    const u32 prev_index = prev < 3 ? prev : 0;
    if (_3a00[prev_index]->_130 == page) {
        index = prev;
    } else {
        const u8 cur = wrapTab(tab);
        const u32 cur_index = cur < 3 ? cur : 0;
        if (_3a00[cur_index]->_130 == page) {
            index = cur;
        } else {
            const u8 next = wrapTab(u8(tab + 1));
            const u32 next_index = next < 3 ? next : 0;
            if (_3a00[next_index]->_130 != page)
                return;
            index = next;
        }
    }
    sub_7100A38FE8(index, false);
}

// NON_MATCHING: the loop induction variable is widened in category comparisons.
void ScreenPauseMenu::sub_7100A379BC(s32 tab) {
    mSelectedCategory = s32(sub_7100A82D08(tab));
    for (s32 i = 0; i < mTabControls.mEntries.size(); ++i) {
        auto& entry = mTabControls.mEntries[i];
        entry.mButton.sub_7100988060(entry.mFirstItemIndex < 0);
        entry.mButton.sub_710098802C(i == mSelectedCategory);
        entry.mPage.sub_7100936A28(sub_7100A82DB8(i));
        if (i == mSelectedCategory)
            entry.mPage.sub_7100936A7C(tab - entry.mFirstItemIndex);
        else
            entry.mPage.sub_7100936AD8();
    }
}

// 0x7100a34a04
void ScreenPauseMenu::sub_7100A34A04() {
    _3bb4 = 1;
}

// 0x7101e7eaf0: model mode for each of the first three pause menu categories (m94 / m98)
static const s32 sUnk_7101e7eaf0[3] = {0, 2, 1};

// 0x7100a36034: the pause menu's per-frame update. It advances the open timer, settles the box cursor
// when the page offset is back at zero, runs the close-button combination's release debounce, steps the
// state machine and the tab pages, and starts / holds the info animators for the two pending bits.
void ScreenPauseMenu::m94() {
    if (_3642) {
        Manager::instance()->sub_7100A7C904();
        return;
    }

    eui::Screen::x_2();

    if (_3c2c && isOpened()) {
        if (_3c30 < UI::instance()->_a8)
            _3c30 += getAnimationStep_();
        else
            _3c2c = false;
    }

    if (_3674 != 0 && _3650 >= -0.001f && _3650 <= 0.001f) {
        _364c = -1;
        _3650 = 0.0f;
        // called through a pointer in the original (not devirtualised)
        if (getStateMachine().getState()->getId() == (&sUnk_71025f0cf0)->getId()) {
            const u32 idx = u32(_3a18) < 3 ? _3a18 : 0;
            if (auto* unit = _3a00[idx])
                unit->sub_71009B0224(true);
        }
        _3674 = 0;
        if (auto* mgr = OnUiActorMgr::instance())
            mgr->_10c = u32(mSelectedCategory) <= 2 ? sUnk_7101e7eaf0[mSelectedCategory] : 4;
    }

    _361c = sub_7100A36400();

    if (!_3ba8) {
        s32 mask = 0;
        if ((_361c & 0x4200) == 0x4200)
            mask = 0x200;
        else if ((_361c & 0x4100) == 0x4100)
            mask = 0x100;
        if (mask != 0) {
            _3ba8 = true;
            _3bac = mask;
            _3bb0 = 0;
        }
    } else {
        const s32 frames = _3bb0;
        ++_3bb0;
        if ((~_361c & (_3bac | 0x4000)) == 0) {
            _3bb0 = 0;
        } else if (frames >= 7) {
            _3ba8 = false;
        }
    }

    getStateMachine().run();
    sub_7100A36784();
    _3a38.sub_7100938090(getAnimationStep_());

    if (_3a19.isOnBit(0)) {
        if (auto* info = sead::DynamicCast<ScreenPauseMenuInfo>(
                eui::ScreenMgr::instance()->getScreen(ScreenId::PauseMenuInfo))) {
            if (auto* animator = info->_36b0) {
                if (animator->mRate != 0.0f) {
                    _3a19.set(1);
                } else {
                    animator->PlayFromCurrent(eui::Animator::PlayType(0), 1.0f);
                    _3a19.reset(1);
                }
            }
        }
    }
    if (_3a19.isOnBit(1)) {
        if (auto* info = sead::DynamicCast<ScreenPauseMenuInfo>(
                eui::ScreenMgr::instance()->getScreen(ScreenId::PauseMenuInfo))) {
            if (auto* animator = info->_36b8) {
                if (animator->mRate != 0.0f) {
                    _3a19.set(2);
                } else {
                    animator->PlayFromCurrent(eui::Animator::PlayType(0), 1.0f);
                    _3a19.reset(2);
                }
            }
        }
    }
}

// 0x7101e79508: the direction mask of each box cursor move mode (modes 3-6)
static const s32 sUnk_7101e79508[4] = {0x400, 0x8, 0x1000, 0x2};

// 0x7100a36400: the pause menu's button mask for this frame. A decided button wins, then the face /
// direction triggers, then the box cursor's move direction; otherwise the hold / repeat state that
// continues a close or a page move from the previous frame's mask (`_361c`).
// NON_MATCHING: the 0x200 arm's csel lands in w0 (the original keeps the mask in w20 and shares the
// tst / csel tail with the 0x100 arm) and the epilogue's mov w0, w20 is scheduled one load earlier.
u32 ScreenPauseMenu::sub_7100A36400() {
    u32 mask = 0;
    if (mButtonGroup->FindDownButton()) {
        mask = 1;
    } else if (isTrigMaybe(0x1)) {
        mask = 0x4002;
    } else if (isTrigMaybe(0x2)) {
        mask = 0x4004;
    } else if (isTrigMaybe(0x8)) {
        mask = 0x4008;
    } else if (isTrigMaybe(0x10)) {
        mask = 0x4010;
    } else if (isTrigMaybe(0x40)) {
        mask = 0x4020;
    } else if (isTrigMaybe(0x4020)) {
        mask = 0x4200;
    } else if (isTrigMaybe(0x2004)) {
        mask = 0x4100;
    } else if (isTrigMaybe(0x08000000)) {
        mask = 0x4080;
    } else if (isTrigMaybe(0x04000000)) {
        mask = 0x4040;
    } else {
        switch (eui::ScreenMgr::instance()->getBoxCursorMgr()->mMode) {
        case eui::BoxCursorMgr::Mode::_3:
            mask = 0x400;
            break;
        case eui::BoxCursorMgr::Mode::_4:
            mask = 0x8;
            break;
        case eui::BoxCursorMgr::Mode::_5:
            mask = 0x1000;
            break;
        case eui::BoxCursorMgr::Mode::_6:
            mask = 0x2;
            break;
        default:
            if (_361c & 0x200) {
                mask = 0x10040;
                if (isHoldMaybe(0x4020))
                    mask += 0x1c0;
                else
                    mask = 0;
            } else if (_361c & 0x100) {
                mask = 0x10040;
                if (isHoldMaybe(0x2004))
                    mask += 0xc0;
                else
                    mask = 0;
            } else if (_361c & 0x80) {
                mask = 0x10040;
                if (isHoldMaybe(0x08000000))
                    mask += 0x40;
                else
                    mask = 0;
                if ((_292 & 0x40) && sub_71010AA9D0() && mUIController &&
                    mUIController->isRepeat(0x08000000))
                    mask |= 0x8080;
            } else if (_361c & 0x40) {
                mask = 0x10040;
                if (!isHoldMaybe(0x04000000))
                    mask = 0;
                if ((_292 & 0x40) && sub_71010AA9D0() && mUIController &&
                    mUIController->isRepeat(0x04000000))
                    mask |= 0x8040;
            } else {
                mask = 0;
            }
            break;
        }
    }
    return mask;
}

// 0x7100a37a78: opens / closes the two guide layouts for the current (or target) page and tells the
// selected tab's guide control which of them to show.
// NON_MATCHING: the compiler reorders the two _3620 comparisons (ours compares the second result first),
// duplicates the show blocks for the two paths that reach them and colours the flags differently.
void ScreenPauseMenu::sub_7100A37A78() {
    if (!mFirstGuideLayout || !mSecondGuideLayout)
        return;

    bool show_first = false;
    bool show_second = false;
    if (getTabIndex(_3644) != -1) {
        const s32* current_ptr = _3674 != 0 ? &_3648 : &_3644;
        const s32 current = *current_ptr;
        const s32 next = current + 1;
        if (_3620 != -1) {
            show_first = _3620 == s32(sub_7100A82D08(current - 1));
            show_second = _3620 == s32(sub_7100A82D08(next));
        } else if (current >= -1) {
            const s32 num = _3624;
            if (current >= 1)
                show_first = current <= num && num > 0;
            show_second = next < num && num > 0;
        }
    }

    if (show_first) {
        mFirstGuideLayout->sub_7100BDDE7C(false, 1, true);
        mFirstGuideLayout->_70->PlayAuto(1.0f);
    } else {
        mFirstGuideLayout->startAnimCloseImpl_(false, true);
    }
    if (show_second) {
        mSecondGuideLayout->sub_7100BDDE7C(false, 1, true);
        mSecondGuideLayout->_70->PlayAuto(1.0f);
    } else {
        mSecondGuideLayout->startAnimCloseImpl_(false, true);
    }

    if (mSelectedCategory == -1) {
        for (auto& entry : mTabControls.mEntries)
            entry.mGuide.sub_7100936BD4(false, false);
    } else {
        const u32 index = u32(mSelectedCategory) < 7 ? mSelectedCategory : 0;
        mTabControls.mEntries[index].mGuide.sub_7100936BD4(show_first, show_second);
    }
}

// 0x7100a39698: selects the category / tab that holds `page`, moves its page control to the page and
// refreshes the info screen.
void ScreenPauseMenu::sub_7100A39698(s32 page) {
    const s32 category = s32(sub_7100A82D08(page));
    if (category == -1)
        return;

    const u32 index = u32(category) < 7 ? category : 0;
    if (mSelectedCategory == category) {
        mTabControls.mEntries[index].mPage.sub_7100936A7C(
            page - mTabControls.mEntries[index].mFirstItemIndex);
        return;
    }

    mTabControls.mEntries[index].mButton.sub_710098802C(true);
    mTabControls.mEntries[index].mPage.sub_7100936A7C(
        page - mTabControls.mEntries[index].mFirstItemIndex);
    mTabControls.mEntries[u32(mSelectedCategory) < 7 ? mSelectedCategory : 0]
        .mButton.sub_710098802C(false);
    mTabControls.mEntries[u32(mSelectedCategory) < 7 ? mSelectedCategory : 0]
        .mPage.sub_7100936AD8();
    mSelectedCategory = category;

    if (auto* info = sead::DynamicCast<ScreenPauseMenuInfo>(
            eui::ScreenMgr::instance()->getScreen(ScreenId::PauseMenuInfo)))
        info->sub_7100A3081C(mSelectedCategory, true);
}

// 0x7100a37d0c
void ScreenPauseMenu::m99() {
    if (_3664.isUndef()) {
        if (auto* pane = findPane_("B_Page20_00"))
            eui::CalcPaneBoundBox(&_3664, *pane);
    }
    if (Manager::instance()->_64c24 == 1) {
        if (_3a30 == 0) {
            if (_3bb4 == 1)
                getStateMachine().changeState(&sUnk_71025f0ed0);
            else
                getStateMachine().changeState(&sUnk_71025f0cf0);
        } else if (_3a30 == 2) {
            getStateMachine().changeState(&sUnk_71025f0ff0);
        } else {
            getStateMachine().changeState(&sUnk_71025f0f90);
        }
    }
    if (auto* mgr = OnUiActorMgr::instance())
        mgr->sub_7100907914(true);
}

// 0x7100a34a80
bool ScreenPauseMenu::sub_7100A34A80() {
    if (!isOpened() || _3c2c)
        return false;
    if (getStateMachine().getState()->getId() == (&sUnk_71025f0cf0)->getId()) {
        if (_3674 == 0)
            return true;
        const f32 offset = _3650 > 0.0f ? _3650 : -_3650;
        return offset < 70.0f;
    }
    if (getStateMachine().getState()->getId() == (&sUnk_71025f0f90)->getId()) {
        if (_3b90)
            return !_3b90->sub_71009BA010();
        return false;
    }
    return getStateMachine().getState()->getId() == (&sUnk_71025f0ff0)->getId();
}

// 0x7100a38994
void ScreenPauseMenu::adjstBoxCursor(sead::BoundBox2<f32>* box, const eui::BoxCursorNode*) const {
    if (!_3674)
        return;
    if (_3664.isUndef())
        return;
    if (_3664.isInside(box->getMin()) && _3664.isInside(box->getMax()))
        return;
    if (auto* screen = eui::ScreenMgr::instance()->getScreen(ScreenId::BoxCursorTV))
        screen->close(-4);
}

// The pause menu TU's merged .bss block starts with the uiTUStatics.h objects and one extra FLT_MAX
// vector pair; the statics below then land at +0x150 .. +0x180 as in the original initialiser
// 0x7100a3324c.
namespace {
sead::Vector2f sMaxVector2{std::numeric_limits<f32>::max(), std::numeric_limits<f32>::max()};
}

// 0x71025f1210: layout name of the first page.
static sead::SafeString sUnk_71025f1210 = "PauseMenu_00";
// 0x71025f11f0: the three page layout names.
static sead::SafeString sUnk_71025f11f0[3] = {"PauseMenu_00", "N_Slide_01", "N_Slide_02"};
static sead::Buffer<sead::SafeString> sUnk_71025f1200(sUnk_71025f11f0);

// 0x71025f1220: first button tag of each of the three pause menu pages (set up by the TU initialiser 0x7100a3324c)
static s32 sUnk_7102493538[] = {9, 29, 49};
static sead::Buffer<s32> sUnk_71025f1220(sUnk_7102493538);

// 0x71025f1400: the pause menu's icon panes, indexed by the icon id.
struct PauseMenuIcon {
    s32 id;
    sead::SafeString pane;
};
static PauseMenuIcon sUnk_71025f1400[14] = {
    {0, "Pa_IconKagoG_00"},        {1, "Pa_IconKagoR_00"},       {2, "Pa_IconKagoY_00"},
    {3, "Pa_IconKagoB_00"},        {4, "Pa_IconDungeonClear_00"}, {5, "Pa_IconWarpDLC_00"},
    {6, "PaIconDLCAkashiG_00"},    {7, "PaIconDLCAkashiR_00"},   {8, "PaIconDLCAkashiY_00"},
    {9, "PaIconDLCAkashiB_00"},    {10, "Pa_IconDLCKagoG_00"},   {11, "Pa_IconDLCKagoR_00"},
    {12, "Pa_IconDLCKagoY_00"},    {13, "Pa_IconDLCKagoB_00"},
};
static sead::Buffer<PauseMenuIcon> sUnk_71025f1230(sUnk_71025f1400);

// 0x7100a350ac
const char* ScreenPauseMenu::getLayoutName_() const {
    return sUnk_71025f1210.cstr();
}

// 0x7100a39820 (placeholder name): the icon table index of `id`, -1 when the icon is not listed.
s32 sub_7100A39820(s32 id) {
    if (id == -1)
        return -1;
    for (s32 i = 0; i < 14; ++i) {
        if (sUnk_71025f1230[i].id == id)
            return i;
    }
    return -1;
}

// 0x7100a382e0 (placeholder name): refreshes the categories of the page before / at / after `page`.
// NON_MATCHING: the inlined wrapTab keeps the sign-extended argument in a second register in the
// original; ours re-sign-extends after the first select and masks the result again (two extra
// instructions, different registers).
void ScreenPauseMenu::sub_7100A382E0(s32 page) {
    s32 index = 2;
    if (page < sUnk_71025f1220[2])
        index = page >= sUnk_71025f1220[1] ? 1 : 0;
    if (!_3a00[index])
        return;
    const u8 prev = wrapTab(u8(index - 1));
    const u32 prev_index = prev < 3 ? prev : 0;
    if (auto* unit = _3a00[prev_index]) {
        const s32 category = unit->_130;
        if (category >= 0)
            sub_7100A82D08(category);
    }
    if (auto* unit = _3a00[index]) {
        const s32 category = unit->_130;
        unit->sub_71009B0484(page);
        if (category >= 0)
            sub_7100A82D08(category);
    }
    const u8 next = wrapTab(u8(index + 1));
    const u32 next_index = next < 3 ? next : 0;
    if (auto* unit = _3a00[next_index]) {
        const s32 category = unit->_130;
        if (category >= 0)
            sub_7100A82D08(category);
    }
}

// 0x7100a3ad30 (placeholder name): holds the item under the cursor on the current page.
void ScreenPauseMenu::sub_7100A3AD30() {
    s32 index = 0;
    if (sUnk_71025f1220[2] <= _3638)
        index = 2;
    else if (sUnk_71025f1220[1] <= _3638)
        index = 1;
    if (!_3a00[index])
        return;
    const s32 category = _3a00[index]->_130;
    const s32 value = _3a00[index]->sub_71009B0484(_3638);
    const s32 button = _3a00[index]->sub_71009B0468(_3638);
    mPauseMenuDataMgr->holdOrTrashItem(category, value, 0);
    auto* unit = _3a00[index];
    const s32 item = mPauseMenuDataMgr->x_25(category, value);
    unit->mButtons[button].sub_710098975C(item);
    if (auto* info = sead::DynamicCast<ScreenPauseMenuInfo>(
            eui::ScreenMgr::instance()->getScreen(ScreenId::PauseMenuInfo)))
        info->sub_7100A30380(mPauseMenuDataMgr->getNextGrabbedItemIndex());
    if (auto* mgr = OnUiActorMgr::instance()) {
        const s32 grabbed = mPauseMenuDataMgr->getNextGrabbedItemIndex();
        mgr->sub_7100907C34(&grabbed);
    }
}

// 0x7100a3b144 (placeholder name): whether the pause menu may act on the current item.
// NON_MATCHING: our clang folds the three `if (x == 4) return true; return false;` pairs into one shared
// `cset` block and encodes the value test as cmp #1 / b.lt; the original keeps four `return true` blocks
// and compares against zero.
bool ScreenPauseMenu::sub_7100A3B144() {
    if (!sub_7100A82E38())
        return false;
    if (_3630 && _3630->isInInventory() && _3630->getValue() > 0) {
        if (_3630->getType() == PouchItemType::Material)
            return true;
        return false;
    }
    if (_3674 == 0) {
        if (mSelectedCategory == s32(PouchCategory::Material))
            return true;
    } else {
        const s32 page = _3648;
        const PouchCategory category = sub_7100A82D08(page);
        if (category != PouchCategory::Material) {
            if (category != PouchCategory::Invalid)
                return false;
            if (page == mTabControls.mEntries[0].mFirstItemIndex)
                return false;
            if (page == mTabControls.mEntries[1].mFirstItemIndex)
                return false;
            if (page == mTabControls.mEntries[2].mFirstItemIndex)
                return false;
            if (page == mTabControls.mEntries[3].mFirstItemIndex)
                return false;
            if (page != mTabControls.mEntries[4].mFirstItemIndex)
                return false;
        }
        if (!mActiveCursorNode)
            return false;
        const s32 tag = mActiveCursorNode->mButton->mTag;
        if (u32(tag - 9) > 0x3b)
            return false;
        s32 index = 0;
        if (sUnk_71025f1220[2] <= tag)
            index = 2;
        else if (sUnk_71025f1220[1] <= tag)
            index = 1;
        auto* unit = _3a00[index];
        if (!unit)
            return false;
        const PouchCategory category2 = sub_7100A82D08(unit->_130);
        if (category2 == PouchCategory::Material)
            return true;
        if (category2 != PouchCategory::Invalid)
            return false;
        if (unit->_130 == mTabControls.mEntries[0].mFirstItemIndex)
            return false;
        if (unit->_130 == mTabControls.mEntries[1].mFirstItemIndex)
            return false;
        if (unit->_130 == mTabControls.mEntries[2].mFirstItemIndex)
            return false;
        if (unit->_130 == mTabControls.mEntries[3].mFirstItemIndex)
            return false;
        if (unit->_130 != mTabControls.mEntries[4].mFirstItemIndex)
            return false;
        return true;
    }
    return false;
}

// 0x7100a3aee4 (placeholder name): holds the item under the cursor. When the item is equipped, it clears the
// item's equipment slot record, equips the slot's default item, refreshes the info screen and marks the UI busy
// first.
void ScreenPauseMenu::sub_7100A3AEE4() {
    u8 index = 0;
    if (sUnk_71025f1220[2] <= _3638)
        index = 2;
    else if (sUnk_71025f1220[1] <= _3638)
        index = 1;
    if (!_3a00[index])
        return;
    const s32 category = _3a00[index]->_130;
    const s32 value = _3a00[index]->sub_71009B0484(_3638);
    const s32 button = _3a00[index]->sub_71009B0468(_3638);
    if (_3630->isEquipped()) {
        mPauseMenuDataMgr->x_20(category, value);
        const auto* item = _3630;
        const u8 slot = u8(getCreateEquipmentSlot(item->getType()));
        _3bd8[slot].mItem = nullptr;
        _3bd8[slot].mChanged = true;
        if (auto* mgr = OnUiActorMgr::instance())
            mgr->sub_7100907F80(
                mPauseMenuDataMgr->getDefaultEquipment(EquipmentSlot(item->getType())), -1, true);
        if (_3630->getType() == PouchItemType::Bow)
            sub_7100A399F4(category, index);
        if (auto* info = sead::DynamicCast<ScreenPauseMenuInfo>(
                eui::ScreenMgr::instance()->getScreen(ScreenId::PauseMenuInfo)))
            info->sub_7100A2FD64(_3630, false);
        sub_7100A9B9F8(0);
    }
    mPauseMenuDataMgr->holdOrTrashItem(category, value, 0);
    _3a00[index]->sub_71009B00E0(button);
    _3be8[button].sub_7100932FDC(_3bf8, false);
}

// 0x7100a3a7fc
// NON_MATCHING: the original keeps the page index in a separate 64-bit register for the element
// address; our clang reuses the 32-bit index with uxtw.
bool ScreenPauseMenu::sub_7100A3A7FC(s32 page, s32 offset) {
    s32 i = 0;
    for (; i < 3; ++i) {
        if (_3a00[i] && _3a00[i]->_130 == page)
            break;
    }
    if (i == 3)
        return false;
    const s32 tag = sUnk_71025f1220[i] + offset;
    if (tag == 0)
        return false;
    if (getStateMachine().getState()->getId() == (&sUnk_71025f0cf0)->getId()) {
        moveBoxCursorByTag_(tag);
        if (auto* button = mButtonGroup->FindButtonByTag(tag))
            button->setFlag10(true);
    } else {
        _3b80 = tag;
    }
    return true;
}

// 0x71009b0618
ScreenChildEx::ScreenChildEx(eui::LayoutEx* layout) : ScreenChild(layout) {
    _128 = nullptr;
}

ScreenChildEx* ScreenChildEx::sub_71009B064C(s32 group, s32 index) {
    return nn::font::DynamicCast<ScreenChildEx>(_128->getChild(group, index));
}

void ScreenChildEx::m54(sead::Heap* heap) {
    _128 = sead::DynamicCast<ScreenEx>(mLayout->mScreen);
    ScreenChild::m54(heap);
}

// 0x71009b0c24
void Unk_710247a6d8::sub_71009B0C24(eui::TraceGaugeControl* gauge) {
    _150 = gauge;
    if (gauge)
        gauge->_6c = false;
}

// 0x71009b0c34: shows `name` as the item name and clears the cook name
void Unk_710247a6d8::sub_71009B0C34(const sead::SafeString& name) {
    {
        eui::MessageString message;
        sub_7100AA2BDC(name, &message);
        setWidgetString(mLayout, "T_ItemName_00", message);
        setWidgetString(mLayout, "T_CookName_00", sead::SafeString::cEmptyString);
    }
    if (_148) {
        eui::MessageString tag_message;
        sub_7100AA2E08(name, &tag_message);
        _148->sub_7100BD9CDC(tag_message, 0);
        _148->sub_7100BD9B5C();
    }
}

// 0x71009b0cf4: shows `name` as the cook name and clears the item name
void Unk_710247a6d8::sub_71009B0CF4(const sead::SafeString& name) {
    {
        eui::MessageString message;
        sub_7100AA2BDC(name, &message);
        setWidgetString(mLayout, "T_CookName_00", message);
        setWidgetString(mLayout, "T_ItemName_00", sead::SafeString::cEmptyString);
    }
    if (_148) {
        eui::MessageString tag_message;
        sub_7100AA2E08(name, &tag_message);
        _148->sub_7100BD9CDC(tag_message, 0);
        _148->sub_7100BD9B5C();
    }
}

// 0x71009b0db4
void Unk_710247a6d8::sub_71009B0DB4(const PouchItem* item) {
    const auto& item_name = item->getName();
    {
        eui::MessageString message;
        sub_7100AA2BDC(item_name, &message);
        setWidgetString(mLayout, "T_ItemName_00", message);
        setWidgetString(mLayout, "T_CookName_00", sead::SafeString::cEmptyString);
    }
    sead::FixedSafeString<64> name;
    sub_7100AA4354(item, &name);
    eui::MessageString tag_message;
    if (_148) {
        if (sub_7100AA2E08(name, &tag_message))
            sub_7100AA2E08(item_name, &tag_message);
        _148->sub_7100BD9CDC(tag_message, 0);
        _148->sub_7100BD9B5C();
    }
}

// 0x71009b0eec
void Unk_710247a6d8::sub_71009B0EEC(u32 frame) {
    if (_130)
        _130->Stop(f32(frame));
    if (frame != 2)
        _1d8.sub_71009C697C();
}

// 0x71009b0fcc: fills the weapon modifier display from a pouch item
void Unk_710247a6d8::sub_71009B0FCC(const PouchItem* item) {
    WeaponStats stats;
    getWeaponStats(*item, &stats);
    _158.sub_71009B25AC(stats, item->getType() == PouchItemType::Bow, item->isEquipped());
}

// 0x71009b1024
// NON_MATCHING: Unk_710247ade8::sub_71009B26A0 is defined in this file and gets inlined
void Unk_710247a6d8::sub_71009B1024() {
    _158.sub_71009B26A0();
}

// 0x71009b102c
void Unk_710247a6d8::sub_71009B102C(const PouchItem* item) {
    ArmorInfo info;
    getArmorInfoMaybe(item->getName(), &info);
    _158.sub_71009B26B8(info, item->isEquipped());
    _1d8.sub_71009C68B8(info.star_num);
}

// 0x71009b108c
// NON_MATCHING: Unk_710247ade8::sub_71009B26B8 is defined in this file and gets inlined
void Unk_710247a6d8::sub_71009B108C(const sead::SafeString& name) {
    ArmorInfo info;
    getArmorInfoMaybe(name, &info);
    _158.sub_71009B26B8(info, false);
    _1d8.sub_71009C68B8(info.star_num);
}

// 0x71009b10ec
void Unk_710247a6d8::sub_71009B10EC(s32 value) {
    if (_150) {
        f32 ratio = 0.0f;
        sub_7100AA8FCC(&ratio, f32(value), 120.0f);
        _150->setTracingSpeed(ratio);
        _150->set50(ratio);
    }
    _190.sub_71009B2010();
}

// 0x71009b1148 (placeholder name): sets the gauge speed from the food's value out of 120 and fills the
// cooking info display.
void Unk_710247a6d8::sub_71009B1148(const CookingInfo& info) {
    if (_150) {
        const s32 value = info.healthRecover;
        f32 ratio = 0.0f;
        sub_7100AA8FCC(&ratio, f32(value), 120.0f);
        _150->setTracingSpeed(ratio);
        _150->set50(ratio);
    }
    _190.sub_71009B1D74(info);
}

// 0x71009b11b8
void Unk_710247a6d8::sub_71009B11B8() {
    if (!_1c8)
        return;
    const f32 time = ksys::gdt::getFlag_MasterSwordRecoverTime();
    const s32 minutes = sead::Mathf::ceil(time / f32(sub_7100AA946C()));
    sub_7100AA3914(_1c8, "T_Time_00", 1, minutes, -1);
    eui::MessageString message;
    getMessage("LayoutMsg/PauseMenuInfo_00", "0011", &message);
    setWidgetString(_1c8, "T_SubText_00", message);
    if (_1d0)
        _1d0->StopAtMax();
}

// 0x71009b12b0
void Unk_710247a6d8::sub_71009B12B0(f32 time) {
    if (!_1c8)
        return;
    const s32 minutes = sead::Mathf::ceil(time / f32(sub_7100AA946C()));
    sub_7100AA3914(_1c8, "T_Time_00", 1, minutes, -1);
    eui::MessageString message;
    getMessage("LayoutMsg/PauseMenuInfo_00", "0010", &message);
    setWidgetString(_1c8, "T_SubText_00", message);
    if (minutes <= 0) {
        if (_1d0)
            _1d0->StopAtMin();
    } else if (_1d0) {
        _1d0->StopAtMax();
    }
}

// 0x7100a3df9c
void ScreenPauseMenu::m179() {
    if ((_361c & 0x24) == 0 || (_361c & 0x4000) == 0)
        return;
    if (auto* mgr = Unk_7102506d38::instance())
        mgr->sub_710109E5D0(mUIController);
    getStateMachine().changeState(&sUnk_71025f0cf0);
}

// 0x7100a3de4c
void ScreenPauseMenu::m178() {
    if (auto* mgr = OnUiActorMgr::instance())
        mgr->toggleFlag1f4Bit0();
    if (auto* info = sead::DynamicCast<ScreenPauseMenuInfo>(
            eui::ScreenMgr::instance()->getScreen(ScreenId::PauseMenuInfo)))
        info->sub_7100A31190(true);
    if (mFirstGuideLayout && mSecondGuideLayout) {
        if (u32(mFirstGuideLayout->_91 - 1) < 2)
            mFirstGuideLayout->startAnimCloseImpl_(false, false);
        if (u32(mSecondGuideLayout->_91 - 1) < 2)
            mSecondGuideLayout->startAnimCloseImpl_(false, false);
        if (mSelectedCategory != -1) {
            const s32 idx = u32(mSelectedCategory) < 7 ? mSelectedCategory : 0;
            mTabControls.mEntries[idx].mGuide.sub_7100936BD4(false, false);
        }
    }
}

// 0x7100a3e004
void ScreenPauseMenu::m180() {
    if (auto* mgr = OnUiActorMgr::instance())
        mgr->toggleFlag1f4Bit0();
    if (auto* info = sead::DynamicCast<ScreenPauseMenuInfo>(
            eui::ScreenMgr::instance()->getScreen(ScreenId::PauseMenuInfo))) {
        if (_3640)
            info->sub_7100A30DF0(true);
        else
            info->sub_7100A3081C(mSelectedCategory, true);
    }
    sub_7100A392D8();
}

// 0x7100a21604
void ScreenMainShortCut::sub_7100A21604(s32 index) {
    if (u32(index) < 0x15 && _3720 != -1) {
        _3864 = _386c[index];
        sub_7100A21668();
        invokeSoundLink2Event_("mc_ShortCut_Change");
    }
}

// 0x71009b0f3c
void Unk_710247a6d8::sub_71009B0F3C(bool on) {
    if (!_138)
        return;
    if (on)
        _138->StopAtMax();
    else
        _138->StopAtMin();
}

// 0x71009b0f60
void Unk_710247a6d8::sub_71009B0F60(bool on) {
    if (!_140)
        return;
    if (on) {
        _140->StopAtMin();
        return;
    }
    _140->StopAtMax();
    if (_130)
        _130->Stop(0.0f);
    _1d8.sub_71009C697C();
}

// 0x71009b0818
// NON_MATCHING: the ScreenChildEx constructor above is inlined here; the original calls it
Unk_710247a6d8::Unk_710247a6d8(eui::LayoutEx* layout) : ScreenChildEx(layout) {}

// 0x71009b1a6c
Unk_710247ada8::Unk_710247ada8() = default;

// 0x71009b1a90
Unk_710247ada8::~Unk_710247ada8() {
    mIcons.freeBuffer();
}

// 0x71009b1b74 (placeholder name): binds the layout and heap, creates the Gauge / Type animators and the three
// Pa_SpIcon_NN icon slots
// NON_MATCHING: register allocation and the 0x80 vs 0xa0 stack frame differ (the original keeps the array base and the
// 3 in x20 / x23 through the unrolled loop); the body, allocation and calls are the same.
void Unk_710247ada8::sub_71009B1B74(eui::LayoutEx* layout, sead::Heap* heap) {
    if (!layout || !heap)
        return;
    mLayout = layout;
    _18 = layout->createAnimatorAuto("Gauge", false);
    _20 = mLayout->createAnimatorAuto("Type", false);
    mIcons.setBuffer(3, new (heap, 8, std::nothrow) Unk_71024774c8[3]);
    sead::FixedSafeString<0x20> name;
    name.format("Pa_SpIcon_%02d", 0);
    mIcons[0].sub_7100988EF0(mLayout->findPartsLayout(name.cstr()));
    name.format("Pa_SpIcon_%02d", 1);
    mIcons[1].sub_7100988EF0(mLayout->findPartsLayout(name.cstr()));
    name.format("Pa_SpIcon_%02d", 2);
    mIcons[2].sub_7100988EF0(mLayout->findPartsLayout(name.cstr()));
}

// 0x71009b24c4
Unk_710247ade8::Unk_710247ade8() = default;

// 0x71009b24e4
Unk_710247ade8::~Unk_710247ade8() = default;

// 0x71009b252c (placeholder name): binds the layout and creates the Num / Color animators and the icon layout
void Unk_710247ade8::sub_71009B252C(eui::LayoutEx* layout) {
    if (!layout)
        return;
    _8 = layout;
    _10 = layout->createAnimatorAuto("Num", false);
    _18 = _8->createAnimatorAuto("Color", false);
    _20.sub_7100988EF0(_8->findPartsLayout("Pa_SpIcon_00"));
}

// 0x71009b25ac (placeholder name): shows the weapon modifier text and drives the icon animators
void Unk_710247ade8::sub_71009B25AC(const WeaponStats& stats, bool is_bow, bool old) {
    if (!_8)
        return;
    if (stats.modifier.flags.isZero()) {
        if (_10)
            _10->StopAtMin();
        return;
    }
    if (_10)
        _10->StopAtMax();
    sub_7100AA73E8(_8, "T_Text_00", stats.modifier);
    f32 frame = -1.0f;
    sub_7100AA7290(stats.modifier, is_bow, &frame);
    _20.sub_7100988F30(frame);
    if (_18) {
        if (old)
            _18->StopAtMax();
        else
            _18->StopAtMin();
    }
}

// 0x71009b26a0
void Unk_710247ade8::sub_71009B26A0() {
    if (_10)
        _10->StopAtMin();
}

// 0x71009b26b8
void Unk_710247ade8::sub_71009B26B8(const ArmorInfo& info, bool old) {
    if (!_8)
        return;

    if (info.effect == -1) {
        if (_10)
            _10->StopAtMin();
        return;
    }

    if (_10)
        _10->StopAtMax();

    setArmorInfoMessage(_8, "T_Text_00", info);

    f32 frame = -1.0f;
    sub_7100AA4ACC(info.effect, &frame);
    _20.sub_7100988F30(frame);

    if (_18) {
        if (old)
            _18->StopAtMax();
        else
            _18->StopAtMin();
    }
}

// 0x71009b5fc8
void ScreenPauseMenuUnk3b98::sub_71009B5FC8(bool active) {
    if (active) {
        // Pointer virtual form retains the original state descriptor getId call.
        if (mStateMachine.getState()->getId() != (&sUnk_710261ee00)->getId())
            return;
        mStateMachine.changeState(&sUnk_71025d98a0);
    } else {
        mStateMachine.changeState(&sUnk_710261ee00);
    }
}

// 0x71009b6040
bool ScreenPauseMenuUnk3b98::sub_71009B6040() {
    // called through a pointer in the original (not devirtualised)
    if (mStateMachine.getState()->getId() == (&sUnk_71025d9900)->getId())
        return true;
    return mStateMachine.getState()->getId() == (&sUnk_71025d9960)->getId();
}


// 0x7100a349f4
bool ScreenPauseMenu::sub_7100A349F4() {
    return _3bb4 == 3;
}

// 0x7100a34a10
bool ScreenPauseMenu::sub_7100A34A10() {
    return _3bb4 != 0;
}

s32 sUnk_710249ad68 = -1;
s32 sUnk_710249ad6c = -1;
s32 sUnk_710249ad70 = -1;
s32 sUnk_710249ad74 = 3;
bool sUnk_71025f5740;
bool sUnk_71025f5741;

// 0x7100a6670c
void ScreenSystemWindow01::sub_7100A6670C() {
    sUnk_710249ad68 = -1;
    sUnk_710249ad6c = -1;
    sUnk_710249ad70 = -1;
    sUnk_71025f5740 = false;
    sUnk_71025f5741 = false;
    sUnk_710249ad74 = 3;
}

// 0x7100a66760
s32 ScreenSystemWindow01::sub_7100A66760() {
    if (isE3DemoMode() && !isRIDDemo())
        return 0;
    if (!sUnk_71025f5740)
        return -1;
    auto* save = SaveSystem::instance();
    if (!save)
        return -1;
    if (sUnk_710249ad6c < 0)
        return -1;
    if (sUnk_710249ad74 != 0)
        return sUnk_710249ad6c;
    return save->isFinishedSavingMaybe() ? sUnk_710249ad6c : -1;
}

// 0x7100a667ec
s32 ScreenSystemWindow01::sub_7100A667EC() {
    if (isE3DemoMode() && !isRIDDemo())
        return 0;
    return sUnk_710249ad70;
}

// 0x7100a66c3c
void ScreenSystemWindow01::sub_7100A66C3C() {
    if (_36b0) {
        _36b0->StopAtMin();
        _36b0->disableKeepLinked();
    }
    if (_36a8)
        _36a8->StopAtMin();
    if (_3698)
        _3698->StopAtMin();
    if (_36a0)
        _36a0->StopAtMin();
    if (_36b8)
        _36b8->StopAtMin();
    if (_3690)
        _3690->StopAtMin();
    if (_3720)
        _3720->StopAtMin();
}

// 0x7100a66d00
void ScreenSystemWindow01::sub_7100A66D00() {
    if (_3610)
        _3610->setFlag10(false);
    if (_3618)
        _3618->setFlag10(false);
    if (_3620)
        _3620->setFlag10(false);
    if (_3628)
        _3628->setFlag10(false);
    if (_3630)
        _3630->setFlag10(false);
    if (_3638)
        _3638->setFlag10(false);
    if (_3640)
        _3640->setFlag10(false);
    if (_3648)
        _3648->setFlag10(false);
}

// 0x7100a67068
void ScreenSystemWindow01::sub_7100A67068() {
    if (_3690->mRate != 0.0f)
        return;

    if (_3690->mFrame == static_cast<f32>(_3690->GetFrameSize())) {
        sub_71010AA894();
        auto* button = mButtonGroup->FindButtonByTag(0x60);
        if (auto* normal = nn::font::DynamicCast<eui::NormalButton>(button))
            normal->DownOff(false);
    } else {
        close(-1);
    }
}

// 0x7100a6716c
// NON_MATCHING: scroll-parameter temporaries and fixed-row creation allocate registers differently.
void ScreenSystemWindow01::m92(sead::Heap* heap) {
    Unk_7102474df8_Params params;
    params.spacing = 94.0f;
    params.corner1.set(0.0f, 0.0f);
    params.corner2.set(0.0f, 0.0f);
    params.count = 6;
    if (auto* pane = static_cast<nn::ui2d::Pane*>(sub_7100A48328("N_SlideArea_00", nullptr))) {
        sead::Vector2f bottom_left, top_left, top_right, bottom_right;
        getPaneCorners(pane, &bottom_left, &top_left, &top_right, &bottom_right);
        params.corner1.x = bottom_left.x < top_right.x ? bottom_left.x : top_right.x;
        params.corner2.x = bottom_left.x < top_right.x ? top_right.x : bottom_left.x;
        params.corner1.y = bottom_left.y < top_right.y ? bottom_left.y : top_right.y;
        params.corner2.y = bottom_left.y < top_right.y ? top_right.y : bottom_left.y;
    }
    const Unk_7102474df8_Speeds speeds;
    _4ad0.sub_7100937FA4(heap, this, &params, &speeds);
    if (auto* parts = eui::sub_7100945088(sub_7100A48104("Pa_File_00", nullptr))) {
        for (s32 i = 5; i > 0; --i) {
            sead::FormatFixedSafeString<64> name("Pa_File_%02d", i);
            auto* layout = sub_7100A47A5C(heap, 1,
                static_cast<eui::LayoutEx*>(parts->mPartsLayoutLink.layout), name, parts, true, true);
            _49e0[i]._10 = layout->GetPane();
        }
        _49e0[0]._10 = static_cast<eui::LayoutEx*>(parts->mPartsLayoutLink.layout)->GetPane();
    }
    for (auto& entry : _49e0)
        _4ad0.sub_7100938408(&entry);
}

// 0x7100a67704: waits until every texture controller is loaded
void ScreenSystemWindow01::m89() {
    bool ready = true;
    for (auto& controller : _3748) {
        if (controller.sub_71009CBEAC()) {
            controller.sub_71009CC3A0();
            ready = false;
        }
        ready &= controller.sub_71009CBFA4();
    }
    if (ready)
        _292 |= 0x20;
}

// 0x7100a68010
void ScreenSystemWindow01::m98() {
    sUnk_710249ad68 = -1;
    sUnk_710249ad6c = -1;
    sUnk_71025f5740 = false;
    sUnk_71025f5741 = false;
    _4b61 = false;
    _4b62 = false;
    _4b7c.init(0.0f);
    x_2();
    if (sUnk_710249ad74)
        _4b60 = !sub_7100A6641C();
}

// 0x7100a680a8
void ScreenSystemWindow01::m99() {
    mButtonGroup->_38 |= 2;
    s32 tag;
    if (sUnk_710249ad74) {
        _3610->setFlag10(false);
        _3618->setFlag10(false);
        tag = 0x62;
    } else {
        _3610->setFlag10(true);
        _3618->setFlag10(true);
        tag = 0x60;
    }
    setReservedBoxCursorNode(findBoxCursorNodeByTag(tag));
    mActiveCursorNode = nullptr;
}

// 0x7100a6818c
void ScreenSystemWindow01::m102(eui::AnimButton* button) {
    const s32 tag = button->mTag;
    if ((tag & ~1) == 0x60) {
        sUnk_710249ad68 = -1;
        return;
    }
    const s32 index = tag - 0x62;
    sUnk_710249ad68 = index;
    _49e0[index].sub_7100937DA4(false);
}

// 0x7100a66824 (placeholder name): whether the window shows the E3-only state
bool ScreenSystemWindow01::sub_7100A66824() {
    if (uking::ui::isE3DemoMode() && !uking::ui::isRIDDemo())
        return false;
    return sUnk_71025f5741 != 0;
}

// 0x7100a6814c (CSV ScreenSystemWindow01::m100)
void ScreenSystemWindow01::m100() {
    if (_4b5c && u32(sUnk_710249ad74 - 1) <= 1)
        invokeSoundLink2Event_("mc_CloseOnlyLoad");
}

// 0x7100a6637c
void ScreenSystemWindow01::m128() {
    for (auto& controller : _3748)
        controller.sub_71009CC970();
}

// 0x7100a663d8 (CSV ScreenSystemWindow01::m129)
void ScreenSystemWindow01::m129() {
    if (sUnk_710249ad74)
        _4b60 = !sub_7100A6641C();
}

// 0x7100a3f3f4
void ScreenPickUp::setItemAndOpen(const sead::SafeString& item, bool show) {
    open(3);
    if (show)
        sub_7100A3F450(item, 5.0f);
}

// 0x7100a3f450
// NON_MATCHING: the original null-checks the found window pointer (the loop exits to the unlock instead of a csel);
// it matches with `if (it->mOrder >= 0) continue; if (PickUpWin* win = it.operator->()) {...} break;`.
void ScreenPickUp::sub_7100A3F450(const sead::SafeString& item, f32 time) {
    mCS.lock();
    PickUpWin* win = nullptr;
    for (auto& entry : mWins) {
        if (entry.mOrder < 0) {
            win = &entry;
            break;
        }
    }
    if (win) {
        for (auto& entry : mWins) {
            if (entry.mOrder >= 0)
                ++entry.mOrder;
        }
        win->mTimer.init(time);
        win->setItem(item);
        if (win->mLayout) {
            nn::ui2d::Pane* pane = win->mLayout->GetPane();
            nn::ui2d::Pane* parent = pane->GetParent();
            parent->RemoveChild(pane);
            parent->AppendChild(pane);
            win->mLayout->GetPane()->SetAlpha(255);
            win->mLayout->sub_7100BDDE7C(false, 0, true);
            if (win->mFlashAnim)
                win->mFlashAnim->PlayAuto(1.0f);
            win->mOrder = 0;
            win->mClosing = false;
        }
    }
    mCS.unlock();
}

// 0x7100a3f5ac
void ScreenPickUp::PickUpWin::setItem(const sead::SafeString& item) {
    mName = item;
    mType = PauseMenuDataMgr::getType(item);
    updateCompareAnim();
    eui::MessageString message;
    sub_7100AA2BDC(mName, &message);
    setWidgetString(mLayout, "T_ItemName_00", message);
    sead::FixedSafeString<128> path;
    sub_7100AA3B50(item, &path, -1);
    requestTexture(path);
}

// 0x7100a3f79c
void ScreenPickUp::m93(sead::Heap* heap) {
    sead::SafeString first_name = "Pa_PickUpWin_00";
    sead::SafeString prefix = "Pa_PickUpWin_";
    if (PickUpWin* win = mWins.emplaceBack()) {
        win->mScreen = this;
        win->mLayout = sub_7100BEAFB0("Pa_PickUpWin_00");
        win->init(heap);
    }
    for (s32 i = 6; i > 0; --i) {
        if (PickUpWin* win = mWins.emplaceBack()) {
            sead::FormatFixedSafeString<32> name("%s%02d", prefix.cstr(), i);
            win->mScreen = this;
            eui::PartsEx* parts = eui::sub_7100945088(sub_7100A48104(first_name, nullptr));
            win->mLayout = sub_7100A47A5C(
                heap, 1, parts ? static_cast<eui::LayoutEx*>(parts->mPartsLayoutLink.layout) : nullptr, name,
                parts, true, true);
            win->init(heap);
        }
    }
}

// 0x7100a3fab4
void ScreenPickUp::PickUpWin::init(sead::Heap* heap) {
    mResHandle = new (heap) ksys::res::Handle;
    mColorAnim = mLayout->tryCreateAnimatorAuto("Color", false);
    if (mColorAnim)
        mColorAnim->StopAtMin();
    mGuideOutAnim = mLayout->tryCreateAnimatorAuto("GuideOut", false);
    if (mGuideOutAnim)
        mGuideOutAnim->StopAtMin();
    mGuideOffAnim = mLayout->tryCreateAnimatorAuto("GuideOff", false);
    if (mGuideOffAnim)
        mGuideOffAnim->StopAtMin();
    mFlashAnim = mLayout->tryCreateAnimatorAuto("Flash", false);
    if (mFlashAnim)
        mFlashAnim->StopAtMin();
    const auto& pos = mLayout->GetPane()->GetPosition();
    mBasePos.x = pos.x;
    mBasePos.y = pos.y;
    mBasePos.z = pos.z;
    mPos = mBasePos;
    mLayout->startAnimCloseImpl_(false, true);
    if (mLayout && mResHandle) {
        if (nn::ui2d::Pane* pane = mLayout->GetPane()->FindPaneByName("P_CaptureItem_00", true)) {
            if (nn::ui2d::Material* material = pane->GetMaterial())
                eui::SetTextureInfoFromTexMap(&mTexInfo, material->GetTexMapArray()[0]);
        }
    }
}

// 0x7100a3fc10
void ScreenPickUp::m94() {
    bool visible = false;
    if (sub_7100AA948C()) {
        visible = true;
        if (sub_7100AA8F10() && ksys::evt::Manager::instance()) {
            auto* event = ksys::evt::Manager::instance()->getActiveEvent();
            if (event && event->mEventName == "Demo049_0")
                visible = false;
        }
    }
    sub_7100AA94C4(mLayout, visible);
    if (sub_7100AA8E5C() || sub_7100AA8F30())
        return;
    mCS.lock();
    for (auto& win : mWins) {
        if (win.mOrder >= 0)
            win.update();
    }
    mCS.unlock();
}

// NON_MATCHING: three spots of scheduling: case 0 keeps &mBasePos in a register across the timer call, case 1 / 2
// load mScreen and &mPos.y after the float constants, and the original computes the alpha before it loads the root
// pane (it matches with a local `const u8 alpha = ...;` before `mLayout->GetPane()->SetAlpha(alpha)`).
// 0x7100a3fd44: moves the window to its place for mOrder (0: shown, 1 / 2: pushed down; later ones slide out
// and fade)
void ScreenPickUp::PickUpWin::update() {
    if (mTextureRequested) {
        if (mResHandle->requestedLoad() && mResHandle->isSuccess() && mResHandle->getResource()) {
            applyTexture();
            mTextureRequested = false;
        } else if (mResHandle->checkLoadStatus() &&
                   mResHandle->getStatus() == ksys::res::Handle::Status::_1) {
            mResHandle->requestUnload2();
            ksys::res::LoadRequest request;
            request.mRequester = "uiPickUpWin_00Screen";
            mResHandle->requestLoad("UI/StockItem/NoImage.bitemico", &request, nullptr);
        }
    }

    if (mLayout && (mLayout->isAnimCloseEnd(false) || mFadedOut) && mClosing) {
        close();
        return;
    }

    switch (mOrder) {
    case 0:
        if (mTimer.updateAndCheckEnded() && mLayout && !mClosing) {
            mLayout->startAnimCloseImpl_(false, false);
            mClosing = true;
        }
        mPos = mBasePos;
        if (mGuideOffAnim && mGuideOffAnim->mFrame == 0.0f && ksys::act::hasTag(mName, ksys::act::tags::Rupee))
            mGuideOffAnim->PlayAuto(1.0f);
        break;
    case 1:
        if (mTimer.updateAndCheckEnded() && mLayout && !mClosing) {
            mLayout->startAnimCloseImpl_(false, false);
            mClosing = true;
        }
        sub_7100AA2350(mScreen, &mPos.y, mBasePos.y + -75.0f, 0.2f, 500.0f, 0.1f);
        if (mGuideOutAnim && mGuideOutAnim->mFrame == 0.0f)
            mGuideOutAnim->PlayAuto(1.0f);
        break;
    case 2:
        if (mTimer.updateAndCheckEnded() && mLayout && !mClosing) {
            mLayout->startAnimCloseImpl_(false, false);
            mClosing = true;
        }
        sub_7100AA2350(mScreen, &mPos.y, mBasePos.y + -150.0f, 0.2f, 500.0f, 0.1f);
        if (mGuideOutAnim && mGuideOutAnim->mFrame == 0.0f)
            mGuideOutAnim->PlayAuto(1.0f);
        break;
    default: {
        mWasInPlace = mInPlace;
        const f32 limit = mBasePos.y + -150.0f;
        sub_7100AA2350(mScreen, &mPos.y, mBasePos.y + -225.0f, 0.2f, 500.0f, 0.1f);
        mInPlace = mPos.y <= limit;
        if (mInPlace) {
            mArrived = !mWasInPlace;
            if (mWasInPlace) {
                if (mTimer.updateAndCheckEnded())
                    mFadedOut = true;
            } else {
                mTimer.init(0.3f);
            }
            if (mLayout)
                mLayout->GetPane()->SetAlpha(s32((1.0f - mTimer.getProgress()) * 255.0f));
        } else {
            mArrived = false;
        }
        if (!mClosing)
            mClosing = true;
        if (mGuideOutAnim && mGuideOutAnim->mFrame == 0.0f)
            mGuideOutAnim->PlayAuto(1.0f);
        break;
    }
    }

    if (mLayout) {
        nn::ui2d::Pane* pane = mLayout->GetPane();
        pane->SetPosition(mPos);
    }
}

// 0x7100a400e0
void ScreenPickUp::m86() {
    mCS.lock();
    for (auto& win : mWins)
        win.close();
    close(-4);
    mCS.unlock();
}

// 0x7100a4014c
void ScreenPickUp::m83() {
    mCS.lock();
    for (auto& win : mWins)
        win.close();
    close(-4);
    mCS.unlock();
}

// 0x7100a401b8
void ScreenPickUp::m91() {
    mCS.lock();
    for (auto& win : mWins)
        win.close();
    close(-4);
    mCS.unlock();
}

// 0x7100a40224
// NON_MATCHING: regalloc only (x8 / x9 swapped for the texture map and &mTexInfo).
void ScreenPickUp::PickUpWin::close() {
    mClosing = false;
    mInPlace = false;
    mWasInPlace = false;
    mArrived = false;
    mFadedOut = false;
    mOrder = -1;
    if (mGuideOutAnim)
        mGuideOutAnim->StopAtMin();
    if (mGuideOffAnim)
        mGuideOffAnim->StopAtMin();
    mLayout->startAnimCloseImpl_(false, true);
    if (mResHandle->requestedLoad() && mResHandle->isSuccess() && mResHandle->getResource()) {
        mResHandle->parseResource(nullptr);
        nn::ui2d::Pane* pane = mLayout->GetPane()->FindPaneByName("P_CaptureItem_00", true);
        if (!pane)
            return;
        nn::ui2d::Material* material = pane->GetMaterial();
        if (!material)
            return;
        sead::Graphics::instance()->lockDrawContext();
        material->GetTexMapArray()[0].ReplaceTextureInfo(&mTexInfo);
        sead::Graphics::instance()->unlockDrawContext();
        mResHandle->requestUnload2();
    }
}

// 0x7100a40360
// NON_MATCHING: regalloc only (x8 / x9 swapped for the texture map and the texture info, as in close()).
void ScreenPickUp::PickUpWin::applyTexture() {
    if (!mLayout || !mResHandle)
        return;
    mResHandle->parseResource(nullptr);
    nn::ui2d::Pane* pane = mLayout->GetPane()->FindPaneByName("P_CaptureItem_00", true);
    if (!pane)
        return;
    nn::ui2d::Material* material = pane->GetMaterial();
    if (!material)
        return;
    auto* resource = mResHandle->getResource();
    if (!resource)
        return;
    auto* texture = sead::DynamicCast<Unk_710247e8c0>(resource);
    sead::Graphics::instance()->lockDrawContext();
    material->GetTexMapArray()[0].ReplaceTextureInfo(&texture->mTexInfo);
    sead::Graphics::instance()->unlockDrawContext();
}

// 0x7100a40328
void ScreenPickUp::m80(bool visible) {
    if (visible)
        sub_7100AA94C4(mLayout, sub_7100AA948C());
    else
        sub_7100AA94C4(mLayout, false);
}

// 0x7100a40470
void ScreenPickUp::PickUpWin::updateCompareAnim() {
    if (!isPouchItemWeapon(mType) || mType == PouchItemType::Arrow) {
        mColorAnim->Stop(0.0f);
        return;
    }
    const PouchItem* equipped = PauseMenuDataMgr::instance()->getEquippedItem(mType);
    if (!equipped || !equipped->isInInventory()) {
        mColorAnim->Stop(0.0f);
        return;
    }
    const PouchItem* item = PauseMenuDataMgr::instance()->getLastAddedItem();
    f32 frame;
    if (item->isInInventory() && item->isEquipped()) {
        frame = 1.0f;
    } else {
        const s32 equipped_value = sub_7100AA7AC8(*equipped);
        const s32 value = item->isInInventory() ? sub_7100AA7AC8(*item) : 0;
        if (equipped_value == value)
            frame = 3.0f;
        else if (equipped_value < value)
            frame = 1.0f;
        else if (equipped_value > value)
            frame = 2.0f;
        else
            frame = 0.0f;
    }
    mColorAnim->Stop(frame);
}

// 0x7100a4055c
void ScreenPickUp::PickUpWin::requestTexture(const sead::SafeString& path) {
    if (mResHandle) {
        if (mResHandle->requestedLoad())
            mResHandle->requestUnload2();
        ksys::res::Handle::Status status{};
        ksys::res::LoadRequest request;
        request.mRequester = "uiPickUpWin_00Screen";
        mResHandle->requestLoad(path, &request, &status);
    }
    mTextureRequested = true;
}

// 0x71009b0b44
eui::AlignPane* sub_71009B0B44(eui::LayoutEx* layout, const char* name) {
    return nn::font::DynamicCast<eui::AlignPane>(layout->mPane->FindPaneByName(name, true));
}

// 0x7100a32f3c
ScreenChild* sub_7100A32F3C(const nn::ui2d::ControlSrc&, eui::LayoutEx* layout) {
    auto* layout_ex = nn::font::DynamicCast<eui::LayoutEx>(layout);
    if (!layout_ex || !layout_ex->mScreen || !layout_ex->mScreen->mInitializeHeap)
        return nullptr;
    return new (layout_ex->mScreen->mInitializeHeap, 8) Unk_710247b428(layout_ex);
}

// 0x7100a33134
ScreenChild* sub_7100A33134(const nn::ui2d::ControlSrc&, eui::LayoutEx* layout) {
    auto* layout_ex = nn::font::DynamicCast<eui::LayoutEx>(layout);
    if (!layout_ex || !layout_ex->mScreen || !layout_ex->mScreen->mInitializeHeap)
        return nullptr;
    return new (layout_ex->mScreen->mInitializeHeap, 8) Unk_710247a028(layout_ex);
}

}  // namespace uking::ui
