#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiTextBoxEx.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiTUStatics.h"
#include <thread/seadCriticalSection.h>
#include <prim/seadScopedLock.h>
#include "Game/gameFlagUtils.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/GameData/gdtSpecialFlagNames.h"

namespace uking::ui {

// The TU's statics; the original merges the layout name into the block at 0x71025eccd0 (after the
// uiTUStatics.h objects). The states are external objects just before it.
static sead::SafeString sLayoutName = "DLCSinJuAkashiNum_00";

ksys::StateTemplate<ScreenDLCSinJuAkashiNum> sUnk_71025ecb40(
    ++ksys::sUnk_71025cb4c8, "ksys::ui::ScreenBaseEx::StateID_Init", &ScreenDLCSinJuAkashiNum::m69, &ScreenDLCSinJuAkashiNum::m70,
    &ScreenDLCSinJuAkashiNum::m71, &ScreenDLCSinJuAkashiNum::m72, &sUnk_710261ee98);
ksys::StateTemplate<ScreenDLCSinJuAkashiNum> sUnk_71025ecba0(
    ++ksys::sUnk_71025cb4c8, "::StateID_Wait", &ScreenDLCSinJuAkashiNum::m154, &ScreenDLCSinJuAkashiNum::m155,
    &ScreenDLCSinJuAkashiNum::m156, &ScreenDLCSinJuAkashiNum::m157, &ksys::sUnk_710250bcd8);
ksys::StateTemplate<ScreenDLCSinJuAkashiNum> sUnk_71025ecc00(
    ++ksys::sUnk_71025cb4c8, "::StateID_NumCount", &ScreenDLCSinJuAkashiNum::m158, &ScreenDLCSinJuAkashiNum::m159,
    &ScreenDLCSinJuAkashiNum::m160, &ScreenDLCSinJuAkashiNum::m161, &ksys::sUnk_710250bcd8);
ksys::StateTemplate<ScreenDLCSinJuAkashiNum> sUnk_71025ecc60(
    ++ksys::sUnk_71025cb4c8, "::StateID_AppearCount", &ScreenDLCSinJuAkashiNum::m162, &ScreenDLCSinJuAkashiNum::m163,
    &ScreenDLCSinJuAkashiNum::m164, &ScreenDLCSinJuAkashiNum::m165, &ksys::sUnk_710250bcd8);

// 0x7100a0464c
const char* ScreenDLCSinJuAkashiNum::getLayoutName_() const {
    return sLayoutName.cstr();
}

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
    getStateMachine().startState(&sUnk_71025ecb40);
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
    getStateMachine().run();
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
        getStateMachine().changeState(&sUnk_71025ecc00);
    } else if (_3638 == 2) {
        getStateMachine().changeState(&sUnk_71025ecc00);
    } else {
        getStateMachine().changeState(&sUnk_71025ecba0);
    }
}

// 0x7100a04c3c
void ScreenDLCSinJuAkashiNum::m155() {
    const s32 count = sub_7100A0488C();
    _361c = count;
    if (_3638 != 0 || _3610) {
        if (_3614 != count)
            getStateMachine().changeState(&sUnk_71025ecc00);
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
            getStateMachine().changeState(&sUnk_71025ecc60);
            break;
        case 2:
            _3638 = 1;
            getStateMachine().changeState(&sUnk_71025ecc60);
            break;
        default:
            getStateMachine().changeState(&sUnk_71025ecba0);
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
        getStateMachine().changeState(&sUnk_71025ecc00);
    } else if (_3620.updateAndCheckEnded()) {
        _3610 = 0;
        close(-1);
    }
}

}  // namespace uking::ui
