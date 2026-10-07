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
        // called through a pointer in the original (not devirtualised)
        mStateMachine.getState()->getId() != (&sUnk_71025f1d70)->getId()) {
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
    // called through a pointer in the original (not devirtualised)
    if (mStateMachine.getState()->getId() != (&sUnk_71025f1d10)->getId())
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

// 0x7100a41354
bool ScreenRupee::sub_7100A41354(bool flag) {
    if (flag) {
        if (_3634 != 0)
            return false;
        close(-1);
        return true;
    }
    if (_3634 == 0)
        return false;
    if (_3634 != 1 && _3634 != 2)
        return false;
    // called through a pointer in the original (not devirtualised)
    if (_3610 || mStateMachine.getState()->getId() == (&sUnk_71025f1cb0)->getId()) {
        _3634 = 3;
        return false;
    }
    if (_3634 == 1) {
        close(-1);
        return true;
    }
    mStateMachine.changeState(&sUnk_71025f1d10);
    _3634 = 3;
    return true;
}

// 0x7100a41440
bool ScreenRupee::sub_7100A41440() {
    if (_3610)
        return true;
    // called through a pointer in the original (not devirtualised)
    return mStateMachine.getState()->getId() == (&sUnk_71025f1cb0)->getId();
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

// 0x7100a410d8
void ScreenRupee::sub_7100A410D8(s32 a1) {
    _36d0.lock();
    const s32 mode = _3634;
    if (a1 != 0) {
        if (mode != 0) {
            s32 cur = mode;
            if (mode == 4) {
                _3614 = ksys::gdt::getFlag_CurrentRupee(false);
                cur = _3634;
            }
            if (cur >= a1) {
                // called through a pointer in the original (not devirtualised)
                const s32 state_id = mStateMachine.getState()->getId();
                if (state_id == (&sUnk_71025f1d10)->getId()) {
                    const s32 w = _3634;
                    if (w == 2) {
                        mStateMachine.changeState(&sUnk_71025f1c50);
                    } else if (w == 3) {
                        if (a1 == 3) {
                            _361c.init(5.0f);
                        } else {
                            mStateMachine.changeState(&sUnk_71025f1c50);
                        }
                    }
                }
                _3634 = a1;
            }
            if (isOpened())
                sub_7100A41264(_3634);
            else
                open(1);
        }
    } else if (mode != 0) {
        if (mode == 4) {
            open(1);
        } else {
            mStateMachine.startState(&sUnk_71025f1bf0);
            open(2);
        }
        _3634 = 0;
        _3614 = ksys::gdt::getFlag_CurrentTotalGetRupeeInMiniGame(false);
    }
    _36d0.unlock();
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
        // called through a pointer in the original (not devirtualised)
        if (state->getId() != (&sUnk_71025f1c50)->getId() && state->getId() != (&sUnk_71025f1cb0)->getId())
            mStateMachine.changeState(&sUnk_71025f1c50);
    }
}

// 0x7100a41b2c
void ScreenRupee::m166() {
    mLayout->startAnimCloseImpl_(false, false);
}

// 0x7100a41b3c
void ScreenRupee::m167() {
    if (mLayout->isAnimCloseEnd(false)) {
        if (sub_7100A98038(mId)) {
            _100 = 0;
        } else {
            _100 = 1;
            const s32 old_mode = _3634;
            _3634 = 1;
            sub_7100A410D8(old_mode);
        }
    }
}

// 0x7100a41b98
void ScreenRupee::m168() {
    _100 = 1;
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

// 0x7100a0483c
void ScreenDLCSinJuAkashiNum::sub_7100A0483C(s32 mode, s32 kind) {
    _3688 = kind;
    if (_3614 == 0) {
        const s32 count = sub_7100A0488C();
        _3614 = count;
        _3618 = count;
    }
    _3638 = mode;
    open(1);
}

// 0x7100a04978
bool ScreenDLCSinJuAkashiNum::sub_7100A04978() {
    if (_3638 != 0)
        return false;
    // called through a pointer in the original (not devirtualised)
    if (_3610 || mStateMachine.getState()->getId() == (&sUnk_71025ecc00)->getId()) {
        _3638 = 1;
        return false;
    }
    close(-1);
    return true;
}

// 0x7100a04a0c
bool ScreenDLCSinJuAkashiNum::sub_7100A04A0C() {
    if (_3610)
        return true;
    // called through a pointer in the original (not devirtualised)
    return mStateMachine.getState()->getId() == (&sUnk_71025ecc00)->getId();
}

// 0x7100a04a6c
void ScreenDLCSinJuAkashiNum::sub_7100A04A6C(s32 add, s32 kind) {
    _3638 = 2;
    _3688 = kind;
    const s32 count = sub_7100A0488C();
    _3614 = count;
    _3618 = count;
    _361c = count + add;
}

// 0x7100a04aac
void ScreenDLCSinJuAkashiNum::sub_7100A04AAC(s32 kind) {
    if (_3638 == 2) {
        _3688 = kind;
    } else {
        _3610 = true;
        if (mState != 3 && mState != 0)
            return;
        _3688 = kind;
        if (_3614 == 0) {
            const s32 count = sub_7100A0488C();
            _3614 = count;
            _3618 = count;
        }
        _3638 = 0;
    }
    open(1);
}

}  // namespace uking::ui
