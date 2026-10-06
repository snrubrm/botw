#include "Game/UI/uiScreens.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::ui {

// 0x71009cef28
// NON_MATCHING: the original calls StateBase::getId() through the vtable; clang devirtualizes the call on the static state object
bool ScreenAkashNum::sub_71009CEF28() {
    if (_3634 != 0)
        return false;
    if (_3610 || mStateMachine.getState()->getId() == sUnk_71025dc090.getId()) {
        _3634 = 1;
        return false;
    }
    close(-1);
    return true;
}

// 0x71009cefbc
// NON_MATCHING: the original calls StateBase::getId() through the vtable; clang devirtualizes the call on the static state object
bool ScreenAkashNum::sub_71009CEFBC() {
    if (_3610)
        return true;
    return mStateMachine.getState()->getId() == sUnk_71025dc090.getId();
}

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

// 0x71009cf1a4
void ScreenAkashNum::m69() {
    _3614 = 0;
    _3634 = -1;
}

// 0x71009cf220
void ScreenAkashNum::m156() {
    _3610 = false;
}

// 0x71009cf130
void ScreenAkashNum::m99() {
    if (_3634 == 1) {
        _3618 = ksys::gdt::getFlag_DungeonClearSealNum(false);
        mStateMachine.changeState(&sUnk_71025dc090);
    } else if (_3634 == 2) {
        mStateMachine.changeState(&sUnk_71025dc090);
    } else {
        mStateMachine.changeState(&sUnk_71025dc030);
    }
}

// 0x71009cf194
void ScreenAkashNum::m100() {
    mStateMachine.changeState(&sUnk_71025dbfd0);
}

// 0x71009cf1c0
void ScreenAkashNum::m155() {
    const s32 count = ksys::gdt::getFlag_DungeonClearSealNum(false);
    _3618 = count;
    if (_3634 != 0 || _3610) {
        if (_3614 != count)
            mStateMachine.changeState(&sUnk_71025dc090);
    }
}

}  // namespace uking::ui
