#include "Game/UI/uiScreens.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::ui {

// inline-only in the original; name is a guess: the state object that the open / close queries compare with (the call
// through the reference is virtual in the original, a direct use of the object would be devirtualized)
static const ksys::StateBase& getShownState() {
    return sUnk_71025eed10;
}

// 0x7100a0ef5c
void ScreenKologNum::sub_7100A0EF5C(s32 a1) {
    if (_3614 == 0)
        _3614 = ksys::gdt::getFlag_KorokNutsNum(false);
    _3634 = a1;
    open(1);
}

// 0x7100a0f110
void ScreenKologNum::sub_7100A0F110(s32 a1) {
    _3634 = 2;
    s32 num = ksys::gdt::getFlag_KorokNutsNum(false);
    _3614 = num;
    _3618 = num + a1;
}

// 0x7100a0f098
void ScreenKologNum::sub_7100A0F098() {
    if (_3634 != 2) {
        _3610 = 1;
        if (mState != 3 && mState != 0)
            return;
        if (_3614 == 0)
            _3614 = ksys::gdt::getFlag_KorokNutsNum(false);
        _3634 = 0;
    }
    open(1);
}

// 0x7100a0efa4
bool ScreenKologNum::sub_7100A0EFA4() {
    if (_3634 != 0)
        return false;
    if (_3610 || mStateMachine.getState()->getId() == getShownState().getId()) {
        _3634 = 1;
        return false;
    }
    close(-1);
    return true;
}

// 0x7100a0f038
bool ScreenKologNum::sub_7100A0F038() {
    if (_3610)
        return true;
    return mStateMachine.getState()->getId() == getShownState().getId();
}

}  // namespace uking::ui
