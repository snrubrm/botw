#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiTextBoxEx.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "Game/UI/uiScreens.h"
#include <thread/seadCriticalSection.h>
#include <prim/seadScopedLock.h>
#include "Game/gameFlagUtils.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/GameData/gdtSpecialFlagNames.h"

namespace uking::ui {

// 0x7100a0488c
s32 ScreenDLCSinJuAkashiNum::sub_7100A0488C() {
    switch (_3688) {
    case 0:
        return PauseMenuDataMgr::instance()->getItemCount("Obj_DLC_HeroSeal_Goron", true);
    case 1:
        return PauseMenuDataMgr::instance()->getItemCount("Obj_DLC_HeroSeal_Zora", true);
    case 2:
        return PauseMenuDataMgr::instance()->getItemCount("Obj_DLC_HeroSeal_Rito", true);
    case 3:
        return PauseMenuDataMgr::instance()->getItemCount("Obj_DLC_HeroSeal_Gerudo", true);
    default:
        return 0;
    }
}

// 0x7100a04680
void ScreenDLCSinJuAkashiNum::m93(sead::Heap*) {
    _3620.init(5.0f);
    mStateMachine.startState(&sUnk_71025ecb40);
    _3640.sub_71009331C(sub_7100BEAFB0("Pa_PlusMinus_00"),
                        eui::sub_7100933580(mLayout->mPane->FindPaneByName("T_Num_00", true)));
    _3640.set30(mLayout->tryCreateAnimatorAuto("Flash", false));
    _3680 = mLayout->createAnimatorAuto("Pattern", true);
    if (_3680)
        _3680->Stop(0.0f);
}

// 0x7100a04784
void ScreenDLCSinJuAkashiNum::m94() {
    if (isOpened() && sub_7100A98038(mId)) {
        if (mState != 0 && mState != 3) {
            const s32 count = sub_7100A0488C();
            _361c = count;
            _3614 = count;
            sub_7100AA930C(mLayout, "T_Num_00", count, 0, 0);
            close(-1);
        }
        return;
    }
    mStateMachine.run();
}

// 0x7100a04b34
void ScreenDLCSinJuAkashiNum::m98() {
    sub_7100AA930C(mLayout, "T_Num_00", _3614, 0, 0);
    _3640.sub_71009333AC();
    _3680->Stop(static_cast<f32>(_3688));
}

// 0x7100a04bac
void ScreenDLCSinJuAkashiNum::m99() {
    if (_3638 == 1) {
        _361c = sub_7100A0488C();
        mStateMachine.changeState(&sUnk_71025ecc00);
    } else if (_3638 == 2) {
        mStateMachine.changeState(&sUnk_71025ecc00);
    } else {
        mStateMachine.changeState(&sUnk_71025ecba0);
    }
}

// 0x7100a04c3c
void ScreenDLCSinJuAkashiNum::m155() {
    const s32 count = sub_7100A0488C();
    _361c = count;
    if (_3638 != 0 || _3610) {
        if (_3614 != count)
            mStateMachine.changeState(&sUnk_71025ecc00);
    }
}

// 0x7100a04ca4
void ScreenDLCSinJuAkashiNum::m158() {
    const s32 delta = _361c - _3614;
    if (delta != 0) {
        if (sead::Mathi::abs(delta) >= 2) {
            _3640.set38(delta);
        } else if (_3640._30) {
            _3640._30->PlayAuto(1.0f);
        }
        if (delta >= 1)
            invokeSoundLink2Event_("mc_CountUpAkashi");
        else
            invokeSoundLink2Event_("mc_CountDownAkashi");
    }
    _3618 = sub_7100A0488C();
}

// 0x7100a04d48
void ScreenDLCSinJuAkashiNum::m159() {
    if (_3638 != 2) {
        const s32 old_count = _361c;
        const s32 count = sub_7100A0488C();
        if (_3618 != count) {
            _361c = count;
            _3640.set38(count - old_count);
        }
        _3618 = count;
    }
    if (_291 & 2)
        return;
    _3640.sub_71009333CC();
    const s32 step = sub_7100AA92AC(_3614, _361c);
    _3614 += step;
    sub_7100AA930C(mLayout, "T_Num_00", _3614, _361c, step);
    if (_3614 == _361c) {
        switch (_3638) {
        case 1:
            mStateMachine.changeState(&sUnk_71025ecc60);
            break;
        case 2:
            _3638 = 1;
            mStateMachine.changeState(&sUnk_71025ecc60);
            break;
        default:
            mStateMachine.changeState(&sUnk_71025ecba0);
            break;
        }
    }
}

// 0x7100a04e5c
void ScreenDLCSinJuAkashiNum::m162() {
    _3620.init(5.0f);
    _3618 = sub_7100A0488C();
}

// 0x7100a04e94
void ScreenDLCSinJuAkashiNum::m163() {
    s32 count = sub_7100A0488C();
    bool changed = _3618 != count;
    if (changed)
        _361c = count;
    _3618 = count;
    if (changed) {
        mStateMachine.changeState(&sUnk_71025ecc00);
    } else if (_3620.updateAndCheckEnded()) {
        _3610 = 0;
        close(-1);
    }
}

// 0x7100a415b4
void ScreenRupee::m93(sead::Heap*) {
    _361c.init(5.0f);
    mStateMachine.startState(&sUnk_71025f1bf0);
    _3638.sub_71009331C(sub_7100BEAFB0("Pa_PlusMinus_00"),
                        eui::sub_7100933580(mLayout->mPane->FindPaneByName("T_Rupee_00", true)));
    _3638.set30(mLayout->tryCreateAnimatorAuto("Flash", false));
    _3678.sub_71009319C(0, "mc_CountUpRupee", "mc_CountUpRupeeEnd");
    _3678.sub_71009319C(1, "mc_CountDownRupee", "mc_CountDownRupeeEnd");
}

// 0x7100a416f4
void ScreenRupee::m94() {
    if (sub_7100A98038(mId) && isOpened() &&
        !isSameStateId(*mStateMachine.getState(), sUnk_71025f1d70)) {
        mStateMachine.changeState(&sUnk_71025f1d70);
        return;
    }
    mStateMachine.run();
}

// 0x7100a41788
void ScreenRupee::m98() {
    sub_7100AA930C(mLayout, "T_Rupee_00", _3614, 0, 0);
    _3638.sub_71009333AC();
}

// 0x7100a417e8
void ScreenRupee::m99() {
    if (!isSameStateId(*mStateMachine.getState(), sUnk_71025f1d10))
        sub_7100A41264(_3634);
}

// 0x7100a41878
void ScreenRupee::m155() {
    const s32 count = _3634 == 0 ? ksys::gdt::getFlag_CurrentTotalGetRupeeInMiniGame(false) :
                                   ksys::gdt::getFlag_CurrentRupee(false);
    const bool changed = _3614 != count;
    _3618 = count;
    if (changed)
        mStateMachine.changeState(&sUnk_71025f1cb0);
}

// 0x7100a418e4
void ScreenRupee::m158() {
    _3638.set38(_3618 - _3614);
}

// 0x7100a41900
// NON_MATCHING: regalloc only (the original rematerialises the SafeString vtable address for each temporary; ours keeps it in a callee-saved register)
void ScreenRupee::m159() {
    const s32 old_count = _3618;
    if (getFlagInt(&_3618, _3634 == 0 ? ksys::gdt::flagname::CurrentTotalGetRupeeInMiniGame() :
                                        ksys::gdt::flagname::CurrentRupee()))
        _3638.set38(_3618 - old_count);
    if (sub_7100AA8F70() || !sub_7100A9B278() || (_291 & 2))
        return;
    _3638.sub_71009333CC();
    _3610 = 0;
    const s32 step = sub_7100AA92AC(_3614, _3618);
    const s32 value = _3614 + step;
    const s32 target = _3618;
    _3614 = value;
    sub_7100AA930C(mLayout, "T_Rupee_00", value, target, step);
    if (value == target) {
        _3678.sub_7100933294();
        if (_3634 == 3)
            mStateMachine.changeState(&sUnk_71025f1d10);
        else
            mStateMachine.changeState(&sUnk_71025f1c50);
    } else if (_3638._3c) {
        _3678.sub_71009331E8(0);
    } else {
        _3678.sub_71009331E8(1);
    }
}

// 0x7100a41440
bool ScreenRupee::sub_7100A41440() {
    if (_3610)
        return true;
    return isSameStateId(*mStateMachine.getState(), sUnk_71025f1cb0);
}

// 0x7100a414a0
// NON_MATCHING: regalloc only (same SafeString vtable address CSE as m159)
void ScreenRupee::sub_7100A414A0() {
    if (mState == 0 || mState == 3)
        return;
    getFlagInt(&_3618, _3634 == 0 ? ksys::gdt::flagname::CurrentTotalGetRupeeInMiniGame() :
                                    ksys::gdt::flagname::CurrentRupee());
    _3614 = _3618;
    sub_7100AA930C(mLayout, "T_Rupee_00", _3618, 0, 0);
    close(-1);
}

// 0x7100a41264
void ScreenRupee::sub_7100A41264(s32 mode) {
    sead::ScopedLock<sead::CriticalSection> lock(&_36d0);
    if (mode == 3) {
        _3618 = _3634 == 0 ? ksys::gdt::getFlag_CurrentTotalGetRupeeInMiniGame(false) :
                             ksys::gdt::getFlag_CurrentRupee(false);
        mStateMachine.changeState(&sUnk_71025f1cb0);
    } else {
        const ksys::StateBase* state = mStateMachine.getState();
        if (!isSameStateId(*state, sUnk_71025f1c50) && !isSameStateId(*state, sUnk_71025f1cb0))
            mStateMachine.changeState(&sUnk_71025f1c50);
    }
}

// 0x7100a41a6c
void ScreenRupee::m162() {
    if (_3634 == 3)
        _361c.init(5.0f);
    else
        _361c.init(2.0f);
}

// 0x7100a41a90
// NON_MATCHING: only the instruction order differs (the original loads `_3634` before forming `&_3618`)
void ScreenRupee::m163() {
    if (getFlagInt(&_3618, _3634 == 0 ? ksys::gdt::flagname::CurrentTotalGetRupeeInMiniGame() :
                                        ksys::gdt::flagname::CurrentRupee())) {
        mStateMachine.changeState(&sUnk_71025f1cb0);
    } else if (_361c.updateAndCheckEnded()) {
        close(-1);
    }
}

}  // namespace uking::ui
