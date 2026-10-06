#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUnkSingletons.h"

namespace uking::ui {

// 0x71009ef4ec (CSV unnamed)
void ScreenAppMap::sub_71009EF4EC(s32 a1, s32 a2) {
    if (u32(a1 - 3) > 1)
        return;
    _3ad2 = !(a2 & 1);
    UiSubsys1::instance()->sub_7100968AF8(a1);
}

// 0x71009ef51c (CSV unnamed)
void ScreenAppMap::sub_71009EF51C(s32 a1) {
    if (u32(a1) <= 0xe) {
        UiSubsys1::instance()->set128(a1);
        bool ready = UiSubsys1::instance()->sub_7100968BD8();
        if (ready)
            UiSubsys1::instance()->sub_7100968AF8(2);
        else
            UiSubsys1::instance()->sub_7100968AF8(1);
        _3ad2 = 0;
    }
}

}  // namespace uking::ui
