#include "Game/UI/uiPauseMenuDataMgr.h"
#include "Game/UI/uiScreens.h"
#include "Game/gameFlagUtils.h"
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
    if (getFlagInt(&_3618, _3634 == 0 ? ksys::gdt::flagname::CurrentRupee() :
                                        ksys::gdt::flagname::CurrentTotalGetRupeeInMiniGame())) {
        mStateMachine.changeState(&sUnk_71025f1cb0);
    } else if (_361c.updateAndCheckEnded()) {
        close(-1);
    }
}

}  // namespace uking::ui
