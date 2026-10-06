#include <heap/seadFrameHeap.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/E3Mgr.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiManager.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Physics/System/physRayCast.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/Utils/MathUtil.h"
#include "Game/gameRuneMgr.h"

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

}  // namespace uking::ui
