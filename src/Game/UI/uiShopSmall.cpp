#include "Game/UI/uiShopMgr.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "Game/UI/uiScreens.h"

namespace uking::ui {

// 0x7100982a44
bool UiShopMgr::sub_7100982A44(s32 state, NpcShopData* shop_data) {
    _d0 = shop_data;
    sub_71009821F0(state);
    return true;
}

// 0x7100982a60
bool UiShopMgr::sub_7100982A60(s32 state, s32 value) {
    _dc = value;
    sub_71009821F0(state);
    return true;
}

// 0x7100982b9c: the state value the shop menu shows for the selected item.
u32 UiShopMgr::sub_7100982B9C(const ShopItem& item) {
    if (_30 == 6)
        return sub_7100A91F64(item.name, item._60, _dc);
    if (_30 == 9)
        return 0;
    if (_30 == 10)
        return sub_7100A92180(item.name, item._58, _e0);

    if (u32(_30 - 0xb) <= 2)
        return item._6c == 0 ? 0 : 0xf;

    s32 type;
    if (u32(_30 - 3) < 2)
        type = 2;
    else
        type = u32(_30 - 5) < 2 || _30 == 8;

    if (_30 == 4 || _30 == 2) {
        const bool equipped = item._70 != nullptr && item._70->isEquipped();
        return sub_7100A91E84(item.name, type, item._58, equipped);
    }
    return sub_7100A90E40(item.name, item._60, type, item._58);
}

}  // namespace uking::ui
