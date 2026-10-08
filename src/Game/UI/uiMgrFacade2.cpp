#include <heap/seadFrameHeap.h>
#include <math/seadMathCalcCommon.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/E3Mgr.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiManager.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiUI.h"
#include "Game/UI/uiUnkSingletons.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Physics/System/physRayCast.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/Utils/MathUtil.h"
#include "Game/gameHorseColorInfoMgr.h"
#include "Game/gameRoot38.h"
#include "KingSystem/Sound/sndMgr.h"
#include "Game/gameRuneMgr.h"
#include "Game/gameSaveSystem.h"
#include "KingSystem/System/UI/LayoutResourceMgr.h"
#include "KingSystem/System/VFR.h"
#include <nn/ui2d/Pane.h>

namespace uking::ui {

// 0x7100aa0700 (CSV isE3DemoMode)
bool isE3DemoMode() {
    auto* mgr = E3Mgr::instance();
    return mgr && mgr->isDemoMode();
}

// 0x7100aa0718 (CSV isRIDDemo)
bool isRIDDemo() {
    auto* mgr = E3Mgr::instance();
    return mgr && mgr->isRidDemo();
}

// 0x7100aa0730
bool sub_7100AA0730() {
    auto* mgr = E3Mgr::instance();
    return mgr && mgr->isRidDemoAnd28IsOne();
}

// 0x7100aa0748 (CSV ui::createAndLoadScreen)
bool createAndLoadScreen(s32 id, s8 target, bool a3, sead::Heap* heap, s32 mode) {
    if (eui::ScreenMgr::instance()->getScreen(id))
        return false;

    if (!heap)
        heap = getHeap();

    if (mode != -1) {
        eui::ScreenMgr::instance()->loadScreenImpl_(heap, id, target, a3, nullptr);
    } else {
        const char* name = eui::ScreenMgr::instance()->getTargetMgr()->m3(id);
        auto* frame_heap = sead::FrameHeap::create(
            0, name, heap, 8, sead::Heap::HeapDirection::cHeapDirection_Reverse, false);
        if (frame_heap) {
            frame_heap->enableWarning(false);
            eui::ScreenMgr::instance()->loadScreenImpl_(frame_heap, id, target, a3, nullptr);
            frame_heap->freeTail();
            frame_heap->adjust();
        }
    }

    auto* screen = eui::ScreenMgr::instance()->getScreen(id);
    if (!screen)
        return false;
    if (mode == -1)
        screen->setOwnInitializeHeap(true);
    return true;
}

// 0x7100aa08cc (CSV ui::unloadScreen): unloads the screen `id` if it is loaded and has bit 5 of `_292` set; whether it
// is gone.
bool unloadScreen(s32 id) {
    if (auto* screen = sead::DynamicCast<Screen>(eui::ScreenMgr::instance()->getScreen(id))) {
        if (screen->_292 & 0x20) {
            if (eui::ScreenMgr::instance()->getScreen(id)) {
                eui::ScreenMgr::instance()->unloadScreen(id);
                if (!eui::ScreenMgr::instance()->getScreen(id))
                    return true;
            }
        }
    }
    return false;
}

// 0x7100aa09d8 (placeholder name)
bool sub_7100AA09D8(s32 id) {
    auto* mgr = eui::ScreenMgr::instance();
    if (mgr->getScreen(id)) {
        mgr->unloadScreen(id);
        if (!eui::ScreenMgr::instance()->getScreen(id))
            return true;
    }
    return false;
}

// 0x7100aa0aa4 (CSV ui::getScreenWidgetMaybe)
ScreenChildEx* getScreenWidgetMaybe(s32 id, s32 group) {
    auto* mgr = eui::ScreenMgr::instance();
    if (!mgr)
        return nullptr;
    if (auto* screen = sead::DynamicCast<ScreenEx>(mgr->getScreen(id)))
        return sub_71009DE2B8(screen->getChild(group, 0));
    return nullptr;
}

// 0x7100aa0b6c (placeholder name): wraps an angle in degrees into [0, 360).
f32 sub_7100AA0B6C(f32 degrees) {
    while (degrees < 0.0f)
        degrees += 360.0f;
    while (degrees >= 360.0f)
        degrees += -360.0f;
    return degrees;
}

// NON_MATCHING: the original writes the two results back with one 64-bit store built by bfi from the two loaded words
// (ldp w9, w8; bfi x9, x8, #32, #32; str x9); ours uses stp w8, w9 (the same bytes, a different pairing)
// 0x7100aa0bb0 (placeholder name): rotates `vec` by `degrees`.
void sub_7100AA0BB0(sead::Vector2f* vec, f32 degrees) {
    if (!vec)
        return;
    sead::Vector3f rotated{vec->x, vec->y, 0.0f};
    ksys::util::sub_71011EF070(&rotated, degrees * sead::Mathf::deg2rad(1.0f));
    vec->set(rotated.x, rotated.y);
}

// 0x7100aa0c04 (placeholder name): moves `pos` down onto the ground below it (a ray from y = 2000 to y = -500).
void sub_7100AA0C04(sead::Vector3f* pos) {
    sead::Vector3f start = *pos;
    start.y = 2000.0f;
    sead::Vector3f end = *pos;
    end.y = -500.0f;

    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    ksys::act::sub_7100EEACE8(&query);
    query.setStartAndEnd(start, end);
    if (query.worldRayCast(ksys::phys::ContactLayerType::Entity)) {
        sead::Vector3f hit{0.0f, 0.0f, 0.0f};
        query.getHitPosition(&hit);
        pos->y = hit.y;
    }
}

// 0x7100aa0a74
void sub_7100AA0A74(s32 a1) {
    Manager::instance()->sub_7100A7B8CC(a1);
}

// 0x7100aa0a8c
void sub_7100AA0A8C(s32 a1) {
    Manager::instance()->sub_7100A7B92C(a1);
}

// 0x7100a9f4f8
void sub_7100A9F4F8() {
    Manager::instance()->loadStaticInfo(getHeap());
}

// NON_MATCHING: the original tests the hole 4..9 with a 64-bit range compare (`sxtw; sub x9, x8, #4; cmp x9, #6`) and
// then loads the item from a 14-entry table; ours tests the hole with a bit mask (`lsr w8, 0x3c0f, w8`)
// 0x7100a9bcd4 (placeholder name): whether UI rune `rune` is the rune that is selected in the RuneMgr (false for the
// UI runes 4 - 9, which have no RuneMgr item).
bool sub_7100A9BCD4(s32 rune) {
    s32 item;
    switch (rune) {
    case 0:
        item = 2;
        break;
    case 1:
        item = 3;
        break;
    case 2:
        item = 4;
        break;
    case 3:
        item = 5;
        break;
    case 10:
        item = 0;
        break;
    case 11:
        item = 1;
        break;
    case 12:
        item = 6;
        break;
    case 13:
        item = 7;
        break;
    default:
        return false;
    }
    return RuneMgr::instance()->getCurrentItem() == item;
}

// 0x7100a9bebc (placeholder name): whether the player (the current one if null) can use UI rune `rune`.
bool sub_7100A9BEBC(s32 rune, ksys::act::PlayerBase* player) {
    if (!player) {
        auto* info = ksys::act::PlayerInfo::instance();
        if (!info)
            return false;
        player = info->getPlayer();
    }
    if (!player)
        return false;
    if (rune == 8 || rune == 10 || rune == 11)
        return player->x_13();
    if (rune == 1 || rune == 2)
        return player->checkCanUseRuneCommon();

    switch (rune) {
    case 0:
        return player->checkCanUseMagnesis();
    case 3:
        return player->checkCanUseCamera();
    case 12:
        return player->checkCanUseAmiibo();
    case 13:
        return player->checkCanUseMotorcycle();
    default:
        return true;
    }
}

// 0x7100a9f888
bool sub_7100A9F888() {
    auto* mgr = RuneMgr::instance();
    if (mgr && (mgr->_90 & 0x10))
        return mgr->isSelectedRune(5);
    return false;
}

// 0x7100a9f8b0
void sub_7100A9F8B0() {
    createAndLoadScreenIfNeededImpl(ScreenId::PlainScreen, nullptr);
    if (auto* screen = eui::ScreenMgr::instance()->getScreen(ScreenId::PlainScreen))
        screen->open(1);
    if (auto* sound = ksys::snd::SoundMgr::instance())
        sound->sub_71011FC29C();
}

// 0x7100aa85b4
void sub_7100AA85B4(sead::Heap* heap) {
    if (ksys::ui::LayoutResourceMgr::instance()->loadHorseLayout(heap)) {
        if (auto* mgr = HorseColorInfoMgr::instance())
            mgr->sub_710094D018();
    }
}

// 0x7100aa85f8
bool loadHorseLayoutResImpl() {
    auto* mgr = HorseColorInfoMgr::instance();
    if (!mgr || mgr->_2c == 2)
        return ksys::ui::LayoutResourceMgr::instance()->loadHorseLayoutResource();
    return false;
}

// 0x7100aa862c
bool sub_7100AA862C() {
    auto* mgr = HorseColorInfoMgr::instance();
    if (mgr && (mgr->_28 & 2))
        return true;
    return ksys::ui::LayoutResourceMgr::instance()->hasHorseLayoutLoadFailure();
}

// 0x7100aa865c
void sub_7100AA865C() {
    if (ksys::ui::LayoutResourceMgr::instance()->unloadHorseLayout()) {
        if (auto* mgr = HorseColorInfoMgr::instance())
            mgr->sub_710094D0F8();
    }
}

// 0x7100aa8fcc
// NON_MATCHING: same selects, but the original combines the three comparisons into one `or` tree for the final select
// (`mi | (pl & le) | le`) where we select on the `gt` flag directly; clamp / branchy / `ok ? : ` forms all differ more.
bool sub_7100AA8FCC(f32* out, f32 value, f32 max) {
    const f32 ratio = value / max;
    const bool in_range = !(ratio < 0) && !(ratio > 1);
    const f32 percent = ratio < 0 ? 0 : ratio * 100;
    *out = ratio > 1 ? 100 : percent;
    return in_range;
}

// 0x7100aa946c
u32 sub_7100AA946C() {
    auto* vfr = ksys::VFR::instance();
    return vfr ? vfr->getFrameRate() : 30;
}

// 0x7100a9b1bc
bool sub_7100A9B1BC() {
    auto* ui = UI::instance();
    auto* info = ksys::act::InfoData::instance();
    if (info->hasTag(ui->_40.cstr(), 0xdcd7e698u))
        return false;
    auto* mgr = Manager::instance();
    return !mgr || mgr->_64c4d == 0;
}

// 0x7100aa9808
void sub_7100AA9808(nn::ui2d::Pane* pane) {
    if (pane && pane->IsVisible()) {
        pane->Hide();
        Manager::instance()->sub_7100A7FD64(pane);
    }
}

// 0x7100aa94c4
bool sub_7100AA94C4(eui::LayoutEx* layout, bool visible) {
    if (!layout)
        return false;
    nn::ui2d::Pane* pane = layout->mPane;
    if (!pane)
        return false;
    if (!layout->_91)
        return false;
    if (pane->IsVisible() == visible)
        return false;
    pane->SetVisible(visible);
    return true;
}

// 0x7100aa950c
bool sub_7100AA950C(Screen* screen, bool visible) {
    if (screen && !screen->isClosed() && screen->mLayout->mPane->IsVisible() != visible) {
        screen->m80(visible);
        return true;
    }
    return false;
}

// NON_MATCHING: identical instructions; the original keeps the magnitude in w10 and the constant 1 in w9 (ours the
// other way round: abs / fitSign / std::abs / ternary forms give other shapes)
// 0x7100aa92ac (placeholder name): the signed step (1, 20, 50, 500 or 1000 by the size of the distance) from `from`
// towards `to`; 0 when they are equal
s32 sub_7100AA92AC(s32 from, s32 to) {
    if (from == to)
        return 0;
    const s32 diff = to - from;
    const s32 distance = sead::Mathi::abs(diff);
    s32 step;
    if (distance < 50)
        step = 1;
    else if (distance < 500)
        step = 20;
    else if (distance < 1000)
        step = 50;
    else if (distance < 2000)
        step = 500;
    else
        step = 1000;
    return step * (diff > 0 ? 1 : -1);
}

// 0x7100a9f410
void sub_7100A9F410(s32 value) {
    if (Unk_71025d6ac0::instance()) {
        Unk_71025d6ac0::instance()->sub_71009686BC(value);
        Unk_71025d6ac0::instance()->sub_71009686A0(0);
    }
}

// 0x7100a9b5b0 (placeholder name): the original only evaluates the type check of the screen AppMapDungeon (id 34) and
// ignores its result (the use of the cast screen was optimised away; called by SiteBossRoot)
void sub_7100A9B5B0() {
    sead::IsDerivedFrom<ScreenAppMapDungeon>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::AppMapDungeon));
}

// 0x7100a9d664 (placeholder name): resets the rune timers and calls slot 126 of every Screen
void sub_7100A9D664() {
    RuneMgr::instance()->sub_71006757B8();
    for (s32 id = 0; id < 99; ++id) {
        if (auto* screen = sead::DynamicCast<Screen>(eui::ScreenMgr::instance()->getScreen(id)))
            screen->m126();
    }
}

// 0x7100aa8948 (placeholder name): whether a button of the pause menu is held down (the pause menu must have a target)
bool sub_7100AA8948() {
    auto* screen = sead::DynamicCast<Screen>(eui::ScreenMgr::instance()->getScreen(ScreenId::PauseMenu));
    if (screen && eui::ScreenMgr::instance()->getScreenTarget(screen->mId) >= 0)
        return screen->mButtonGroup->FindDownButton() != nullptr;
    return false;
}

// 0x7100aa88a4 (placeholder name): true while the save system is idle; `*out` is set when a slot has both flags
bool sub_7100AA88A4(bool* out) {
    if (!out)
        return false;
    auto* save = SaveSystem::instance();
    if (!save)
        return false;
    if (!save->sub_7100914CE4())
        return false;
    const s32 count = save->sub_71009154A8(0);
    for (s32 i = 0; i < count; ++i) {
        auto* slot = save->sub_7100914DC8(i, false);
        if (slot->_300 && slot->_302) {
            *out = true;
            return true;
        }
    }
    return true;
}

// 0x7100a9f610 / 0x7100a9f74c (placeholder names): call x_2() of the pause menu / seek pad menu background screens
// (SeekPadMenuBG first / PauseMenuBG first)
void sub_7100A9F610() {
    if (!eui::ScreenMgr::instance())
        return;
    if (auto* screen = sead::DynamicCast<ScreenSeekPadMenuBG>(
            eui::ScreenMgr::instance()->getScreen(ScreenId::SeekPadMenuBG)))
        screen->x_2();
    if (auto* screen = sead::DynamicCast<ScreenPauseMenuBG>(
            eui::ScreenMgr::instance()->getScreen(ScreenId::PauseMenuBG)))
        screen->x_2();
}

void sub_7100A9F74C() {
    if (!eui::ScreenMgr::instance())
        return;
    if (auto* screen = sead::DynamicCast<ScreenPauseMenuBG>(
            eui::ScreenMgr::instance()->getScreen(ScreenId::PauseMenuBG)))
        screen->x_2();
    if (auto* screen = sead::DynamicCast<ScreenSeekPadMenuBG>(
            eui::ScreenMgr::instance()->getScreen(ScreenId::SeekPadMenuBG)))
        screen->x_2();
}

// 0x7100a79ec4 (placeholder name)
bool sub_7100A79EC4() {
    return Root38::instance()->hasAnyFlag();
}

// 0x7100a82db8 / 0x7100a82dd0 (placeholder names)
void sub_7100A82DB8(s32 a) {
    PauseMenuDataMgr::instance()->x_37(a);
}

void sub_7100A82DD0(s32 a) {
    PauseMenuDataMgr::instance()->x_38(a);
}

// 0x71010a0de0 (a separate TU from the fade demo screen: the original calls it out of line)
ksys::snd::UiSoundKind sub_71010A0DE0(bool a, bool b, s32 c) {
    s32 kind = a ? 3 : 5;
    if (!a && !b) {
        static const s32 kinds[4] = {0, 1, 2, 4};
        kind = static_cast<u32>(c) < 4 ? kinds[c] : 1;
    }
    return {kind};
}

}  // namespace uking::ui
