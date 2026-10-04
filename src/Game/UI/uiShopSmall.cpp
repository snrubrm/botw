#include "Game/UI/uiShopMgr.h"

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

}  // namespace uking::ui
