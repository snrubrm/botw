#include "Game/UI/uiShopMgr.h"
#include "Game/UI/uiUtils.h"
#include "Game/UI/euiScreen.h"

// UI wrapper functions around uking::ui::UiShopMgr (the 0x7100a94000 TU).
namespace uking::ui {

// 0x7100a9826c
void sub_7100A9826C() {
    if (auto* mgr = UiShopMgr::instance())
        mgr->sub_7100984EF8();
}

// 0x7100a98284
void sub_7100A98284(bool value) {
    if (auto* mgr = UiShopMgr::instance())
        mgr->sub_71009852C0(value);
}

// 0x7100a982a4
void sub_7100A982A4() {
    if (auto* mgr = UiShopMgr::instance())
        mgr->sub_71009853F4();
}

// 0x7100a98304
bool sub_7100A98304() {
    auto* mgr = UiShopMgr::instance();
    if (!mgr)
        return false;
    switch (mgr->_30) {
    case 1:
    case 2:
    case 14:
        return true;
    default:
        return false;
    }
}

// 0x7100a982bc
bool sub_7100A982BC(NpcShopData* shop_data, bool selected) {
    if (!eui::ScreenMgr::instance())
        return false;
    auto* mgr = UiShopMgr::instance();
    if (selected) {
        if (mgr)
            return mgr->sub_7100982A44(1, shop_data);
    } else if (mgr) {
        return mgr->sub_71009821F0(2);
    }
    return false;
}

// 0x7100a98340
void sub_7100A98340() {
    if (auto* mgr = UiShopMgr::instance())
        mgr->sub_7100984988();
}

// 0x7100a98358
void sub_7100A98358() {
    if (auto* mgr = UiShopMgr::instance())
        mgr->sub_7100984BE8();
}

// 0x7100a98370
void sub_7100A98370(NpcShopData* shop_data) {
    if (auto* mgr = UiShopMgr::instance())
        mgr->sub_7100982A44(3, shop_data);
}

// 0x7100a98394
void sub_7100A98394() {
    if (auto* mgr = UiShopMgr::instance())
        mgr->sub_71009821F0(4);
}

// 0x7100a983b0
bool sub_7100A983B0() {
    if (auto* mgr = UiShopMgr::instance()) {
        if (mgr->_30 == 3)
            return true;
    }
    return false;
}

// 0x7100a983dc
bool sub_7100A983DC() {
    if (auto* mgr = UiShopMgr::instance()) {
        if (mgr->_30 == 4)
            return true;
    }
    return false;
}

// 0x7100a98408
void sub_7100A98408(const sead::SafeString& name) {
    if (auto* mgr = UiShopMgr::instance())
        mgr->sub_7100984CA0(name);
}

// 0x7100a98428
void sub_7100A98428(NpcShopData* shop_data) {
    if (auto* mgr = UiShopMgr::instance())
        mgr->sub_7100982A44(5, shop_data);
}

// 0x7100a9844c
bool sub_7100A9844C() {
    if (auto* mgr = UiShopMgr::instance())
        return mgr->_30 == 5;
    return false;
}

// 0x7100a98474
void sub_7100A98474(s32 rank) {
    if (auto* mgr = UiShopMgr::instance())
        mgr->sub_7100982A60(6, rank);
}

// 0x7100a98498
bool sub_7100A98498() {
    if (auto* mgr = UiShopMgr::instance())
        return mgr->_30 == 6;
    return false;
}

// 0x7100a984c0
bool sub_7100A984C0() {
    auto* mgr = UiShopMgr::instance();
    if (mgr && mgr->_30 == 6)
        return mgr->sub_71009816B0(6, 0);
    return false;
}

// 0x7100a984f0
void sub_7100A984F0(NpcShopData* shop_data) {
    if (auto* mgr = UiShopMgr::instance())
        mgr->sub_7100982A44(9, shop_data);
}

// 0x7100a98514
bool sub_7100A98514() {
    if (auto* mgr = UiShopMgr::instance())
        return mgr->_30 == 9;
    return false;
}

// 0x7100a9853c
void sub_7100A9853C() {
    if (auto* mgr = UiShopMgr::instance())
        mgr->sub_71009821F0(10);
}

// 0x7100a98558
bool sub_7100A98558() {
    if (auto* mgr = UiShopMgr::instance())
        return mgr->_30 == 10;
    return false;
}

// 0x7100a98580
void sub_7100A98580() {
    if (auto* mgr = UiShopMgr::instance())
        mgr->sub_7100984EF8();
}

// 0x7100a98598
void sub_7100A98598() {
    if (auto* mgr = UiShopMgr::instance())
        mgr->sub_71009816B0(10, 0);
}

// 0x7100a985b8
void sub_7100A985B8(NpcShopData* shop_data) {
    if (auto* mgr = UiShopMgr::instance())
        mgr->sub_7100982A44(14, shop_data);
}

// 0x7100a99060
void sub_7100A99060(NpcShopData* shop_data) {
    if (auto* mgr = UiShopMgr::instance())
        mgr->sub_7100982A44(11, shop_data);
}

// 0x7100a99084
void sub_7100A99084() {
    if (auto* mgr = UiShopMgr::instance())
        mgr->sub_71009821F0(12);
}

// 0x7100a990a0
void sub_7100A990A0() {
    if (auto* mgr = UiShopMgr::instance())
        mgr->sub_71009821F0(13);
}

// 0x7100a990bc
// NON_MATCHING: the original keeps the `u32(state - 11) < 3` test as a branch to a separate `return true` block; ours folds it into a cset
bool sub_7100A990BC() {
    auto* mgr = UiShopMgr::instance();
    if (!mgr)
        return false;
    switch (mgr->_30) {
    case 11:
    case 12:
    case 13:
        return true;
    default:
        return false;
    }
}

// 0x7100a990ec
void sub_7100A990EC() {
    if (auto* mgr = UiShopMgr::instance())
        mgr->sub_7100984EE0();
}

// 0x7100a99104
// NON_MATCHING: the original branches to the call block on `<= 2` (b.ls) and lays the call out after the return; ours inverts the branch
void sub_7100A99104() {
    auto* mgr = UiShopMgr::instance();
    if (!mgr)
        return;
    switch (mgr->_30) {
    case 11:
    case 12:
    case 13:
        mgr->sub_71009816B0(mgr->_30, 0);
        break;
    }
}

}  // namespace uking::ui
