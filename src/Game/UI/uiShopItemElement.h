#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/Utils/Types.h"

namespace eui {
class Animator;
class LayoutEx;
class MessageString;
}  // namespace eui

namespace uking::ui {

// Placeholder (name is a guess): one row of ScreenShopInfo's _3658 list. Proven members: the
// layout holding the T_Name_00 / T_NumL_00 / T_NumR_00 widgets (+0x20), the "State" animator
// (+0x130, created by sub_71009C2BF4, stopped by sub_71009C2C28) and the texture slot index
// (+0x138, passed to UiTexSlots::unload / sub_7100A81B1C by ScreenShopInfo::sub_7100A52E60).
// The other ~30 methods of its TU (0x71009c0194-0x71009c31f8) are still unnamed.
class ShopInfoItem {
public:
    // 0x71009c2bf4: creates the "State" animator of the layout.
    void sub_71009C2BF4();
    // 0x71009c2c28: stops the animator (no-op when there is none).
    void sub_71009C2C28(u32 value);
    // 0x71009c2c44: shows the shop message in the T_Name_00 widget.
    void sub_71009C2C44(const eui::MessageString& msg);
    // 0x71009c2c8c / 0x71009c2d44: show the counts in the T_NumL_00 / T_NumR_00 widgets.
    void sub_71009C2C8C(u32 value);
    void sub_71009C2D44(u32 value);

    u8 _0[0x20];
    /* 0x20 */ eui::LayoutEx* _20 = nullptr;
    u8 _28[0x130 - 0x28];
    /* 0x130 */ eui::Animator* _130 = nullptr;
    /* 0x138 */ s32 _138 = 0;
};

}  // namespace uking::ui
