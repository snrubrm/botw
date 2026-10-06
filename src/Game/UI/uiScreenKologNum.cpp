#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiTextBoxEx.h"
#include "Game/UI/uiScreens.h"
#include "KingSystem/GameData/gdtSpecialFlagNames.h"
#include "Game/gameFlagUtils.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::ui {

// 0x7100a0eddc
void ScreenKologNum::m93(sead::Heap*) {
    _361c.init(5.0f);
    mStateMachine.startState(&sUnk_71025eec50);
    _3638.sub_71009331C(sub_7100BEAFB0("Pa_PlusMinus_00"),
                        eui::sub_7100933580(mLayout->mPane->FindPaneByName("T_Num_00", true)));
    _3638.set30(mLayout->tryCreateAnimatorAuto("Flash", false));
}

// 0x7100a0f47c
void ScreenKologNum::m162() {
    _361c.init(5.0f);
}

// 0x7100a0f48c
void ScreenKologNum::m163() {
    if (getFlagInt(&_3618, ksys::gdt::flagname::KorokNutsNum())) {
        mStateMachine.changeState(&sUnk_71025eed10);
    } else if (_361c.updateAndCheckEnded()) {
        close(-1);
    }
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
    if (_3610 || isSameStateId(*mStateMachine.getState(), sUnk_71025eed10)) {
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
    return isSameStateId(*mStateMachine.getState(), sUnk_71025eed10);
}

// 0x7100a0f220
void ScreenKologNum::m69() {
    _3614 = 0;
    _3634 = -1;
}

// 0x7100a0eea4
void ScreenKologNum::m94() {
    if (isOpened() && sub_7100A98038(mId)) {
        if (mState != 0 && mState != 3) {
            const s32 count = ksys::gdt::getFlag_KorokNutsNum(false);
            _3618 = count;
            _3614 = count;
            sub_7100AA930C(mLayout, "T_Num_00", count, 0, 0);
            close(-1);
        }
        return;
    }
    mStateMachine.run();
}

// 0x7100a0f14c
void ScreenKologNum::m98() {
    sub_7100AA930C(mLayout, "T_Num_00", _3614, 0, 0);
    _3638.sub_71009333AC();
}

// 0x7100a0f2a8
void ScreenKologNum::m158() {
    if (_3634 == 2) {
        if (_3618 != _3614 && _3638._30)
            _3638._30->PlayAuto(1.0f);
    } else {
        _3638.set38(_3618 - _3614);
    }
}

// 0x7100a0f2fc
// NON_MATCHING: the original tests `_3634 == 2` before `_3634 == 1` and lays the two state arms out the other way round
void ScreenKologNum::m159() {
    if (_3634 != 2) {
        const s32 old_count = _3618;
        if (getFlagInt(&_3618, ksys::gdt::flagname::KorokNutsNum()))
            _3638.set38(_3618 - old_count);
    }
    if (_291 & 2)
        return;
    _3638.sub_71009333CC();
    const s32 current = _3614;
    const s32 target = _3618;
    const s32 step = sub_7100AA92AC(current, target);
    _3614 += step;
    sub_7100AA930C(mLayout, "T_Num_00", _3614, _3618, step);
    if (_3614 == _3618) {
        if (current < target)
            invokeSoundLink2Event_("mc_CountUpKorogNutEnd");
        else
            invokeSoundLink2Event_("mc_CountDownKorogNutEnd");
        switch (_3634) {
        case 2:
            _3634 = 1;
            [[fallthrough]];
        case 1:
            mStateMachine.changeState(&sUnk_71025eed70);
            break;
        default:
            mStateMachine.changeState(&sUnk_71025eecb0);
            break;
        }
    } else if (current < target) {
        invokeSoundLink2Event_("mc_CountUpKorogNut");
    } else {
        invokeSoundLink2Event_("mc_CountDownKorogNut");
    }
}

// 0x7100a0f1ac
void ScreenKologNum::m99() {
    if (_3634 == 1) {
        _3618 = ksys::gdt::getFlag_KorokNutsNum(false);
        mStateMachine.changeState(&sUnk_71025eed10);
    } else if (_3634 == 2) {
        mStateMachine.changeState(&sUnk_71025eed10);
    } else {
        mStateMachine.changeState(&sUnk_71025eecb0);
    }
}

// 0x7100a0f210
void ScreenKologNum::m100() {
    mStateMachine.changeState(&sUnk_71025eec50);
}

// 0x7100a0f29c
void ScreenKologNum::m156() {
    _3610 = false;
}

// 0x7100a0f23c
void ScreenKologNum::m155() {
    const s32 count = ksys::gdt::getFlag_KorokNutsNum(false);
    _3618 = count;
    if (_3634 != 0 || _3610) {
        if (_3614 != count)
            mStateMachine.changeState(&sUnk_71025eed10);
    }
}

}  // namespace uking::ui
