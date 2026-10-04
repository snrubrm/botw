#include "Game/UI/uiScreens.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::ui {

// 0x71009ceee0
void ScreenAkashNum::sub_71009CEEE0(s32 a1) {
    if (_3614 == 0)
        _3614 = ksys::gdt::getFlag_DungeonClearSealNum(false);
    _3634 = a1;
    open(1);
}

// 0x71009cf01c
void ScreenAkashNum::sub_71009CF01C(s32 a1) {
    _3634 = 2;
    s32 num = ksys::gdt::getFlag_DungeonClearSealNum(false);
    _3614 = num;
    _3618 = num + a1;
}

// 0x71009cf058
void ScreenAkashNum::sub_71009CF058() {
    if (_3634 != 2) {
        _3610 = 1;
        if (mState != 3 && mState != 0)
            return;
        if (_3614 == 0)
            _3614 = ksys::gdt::getFlag_DungeonClearSealNum(false);
        _3634 = 0;
    }
    open(1);
}

}  // namespace uking::ui
