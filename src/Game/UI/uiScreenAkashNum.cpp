#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiTextBoxEx.h"
#include "Game/UI/uiScreens.h"
#include "KingSystem/GameData/gdtSpecialFlagNames.h"
#include "Game/gameFlagUtils.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::ui {

// 0x71009ced60
void ScreenAkashNum::m93(sead::Heap*) {
    _361c.init(5.0f);
    mStateMachine.startState(&sUnk_71025dbfd0);
    _3638.sub_71009331C(sub_7100BEAFB0("Pa_PlusMinus_00"),
                        eui::sub_7100933580(mLayout->mPane->FindPaneByName("T_Num_00", true)));
    _3638.set30(mLayout->tryCreateAnimatorAuto("Flash", false));
}

// 0x71009cee28
void ScreenAkashNum::m94() {
    if (isOpened() && sub_7100A98038(mId)) {
        if (mState != 0 && mState != 3) {
            const s32 count = ksys::gdt::getFlag_DungeonClearSealNum(false);
            _3618 = count;
            _3614 = count;
            sub_7100AA930C(mLayout, "T_Num_00", count, 0, 0);
            close(-1);
        }
        return;
    }
    mStateMachine.run();
}

// 0x71009cf0d0
void ScreenAkashNum::m98() {
    sub_7100AA930C(mLayout, "T_Num_00", _3614, 0, 0);
    _3638.sub_71009333AC();
}

// 0x71009cf22c
void ScreenAkashNum::m158() {
    const s32 delta = _3618 - _3614;
    if (delta == 0)
        return;
    if (sead::Mathi::abs(delta) >= 2) {
        _3638.set38(delta);
    } else if (_3638._30) {
        _3638._30->PlayAuto(1.0f);
    }
    if (delta >= 1)
        invokeSoundLink2Event_("mc_CountUpAkashi");
    else
        invokeSoundLink2Event_("mc_CountDownAkashi");
}

// 0x71009cf2cc
void ScreenAkashNum::m159() {
    if (_3634 != 2) {
        const s32 old_count = _3618;
        if (getFlagInt(&_3618, ksys::gdt::flagname::DungeonClearSealNum()))
            _3638.set38(_3618 - old_count);
    }
    if (_291 & 2)
        return;
    _3638.sub_71009333CC();
    const s32 step = sub_7100AA92AC(_3614, _3618);
    _3614 += step;
    sub_7100AA930C(mLayout, "T_Num_00", _3614, _3618, step);
    if (_3614 == _3618) {
        switch (_3634) {
        case 1:
            mStateMachine.changeState(&sUnk_71025dc0f0);
            break;
        case 2:
            _3634 = 1;
            mStateMachine.changeState(&sUnk_71025dc0f0);
            break;
        default:
            mStateMachine.changeState(&sUnk_71025dc030);
            break;
        }
    }
}

// 0x71009cf3f0
void ScreenAkashNum::m162() {
    _361c.init(5.0f);
}

// 0x71009cf400
void ScreenAkashNum::m163() {
    if (getFlagInt(&_3618, ksys::gdt::flagname::DungeonClearSealNum())) {
        mStateMachine.changeState(&sUnk_71025dc090);
    } else if (_361c.updateAndCheckEnded()) {
        _3610 = 0;
        close(-1);
    }
}

// 0x71009cef28
bool ScreenAkashNum::sub_71009CEF28() {
    if (_3634 != 0)
        return false;
    // called through a pointer in the original (not devirtualised)
    if (_3610 || mStateMachine.getState()->getId() == (&sUnk_71025dc090)->getId()) {
        _3634 = 1;
        return false;
    }
    close(-1);
    return true;
}

// 0x71009cefbc
bool ScreenAkashNum::sub_71009CEFBC() {
    if (_3610)
        return true;
    // called through a pointer in the original (not devirtualised)
    return mStateMachine.getState()->getId() == (&sUnk_71025dc090)->getId();
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
