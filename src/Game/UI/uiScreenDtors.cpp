#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "Game/UI/uiScreens.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "Game/Actor/actRideable.h"

// The trivial destructors of the Screen<Name> classes (defaulted: they tail-call ScreenEx's). Defining them here
// emits the vtables / RTTI of these classes in this TU.
namespace uking::ui {

ScreenGamePadBG::~ScreenGamePadBG() = default;
ScreenWolfLinkHeartGauge::~ScreenWolfLinkHeartGauge() = default;
ScreenMainHorse::~ScreenMainHorse() = default;

// 0x7100a100e0
ScreenMainHorse::ScreenMainHorse() : ScreenEx() {
    memset(&mAnimators, 0, sizeof(mAnimators));
    _3838 = nullptr;
    _3830 = nullptr;
    _3828 = nullptr;
    _3820 = nullptr;
    _3818 = nullptr;
    _3810 = nullptr;
}

// 0x7100a10cd4
void ScreenMainHorse::m101() {
    _3808->disableKeepLinked();
    _3840->disableKeepLinked();
    _3848->disableKeepLinked();
    for (s32 i = 0; i < 10; ++i) {
        mAnimators._3678[i]->disableKeepLinked();
        mAnimators._3718[i]->disableKeepLinked();
        mAnimators._36c8[i]->disableKeepLinked();
    }
    _3810->disableKeepLinked();
    _3818->disableKeepLinked();
    _3820->disableKeepLinked();
}

// 0x7100a10200 (CSV ScreenMainHorse::x): opens the screen when the ridden horse has more than three gears and
// some runnable frames at the top gear, and the ride link is fully set up.
// NON_MATCHING: the gear-limit compare is `cmp #4; b.lt` here, the original tests `cmp #3; b.le` (the same
// predicate; clang canonicalises `<= 3` on an immediate). Everything else (frame, enum stack round trip,
// branch layout, tail call) matches.
void ScreenMainHorse::x() {
    if (u32(mState - 1) > 1) {
        auto* horse = uking::act::PlayerInfo::instance()->getRiddenHorse();
        if (!horse)
            return;
        if (auto* rideable = horse->getRideableMaybe()) {
            const uking::act::RideableBase::S1::UnkGear limit = rideable->mGearMaxNum;
            if (!(int(limit) > 3 && rideable->getRunnableFramesAtGearTop() > 0.0f))
                return;
        }
        if (auto* player = uking::act::PlayerInfo::instance()->getPlayer_()) {
            if (auto* ride_info = player->getPlayerRideInfo()) {
                if ((ride_info->_30 & 3) != 3)
                    return;
            }
        }
        open(1);
    }
}

// 0x7100a102cc
void ScreenMainHorse::sub_7100A102CC() {
    if (isClosed())
        return;
    if (ksys::gdt::getFlag_Horse_IsOnChargePenalty()) {
        for (s32 i = 0; i < _3868; ++i)
            mAnimators._3718[i]->Stop(1.0f);
        _386c = 0;
        _3850.init(1.0f);
    } else if (_3868 != ksys::gdt::getFlag_Horse_CurrentChargeNum()) {
        _3850.init(1.0f);
    } else if (_3850.isDone()) {
        close(-1);
    }
    _3850.update();
}
ScreenReadyGo::~ScreenReadyGo() = default;
ScreenKeyNum::~ScreenKeyNum() = default;
ScreenGameTitle::~ScreenGameTitle() = default;
ScreenDemoName::~ScreenDemoName() = default;
ScreenDemoNameEnemy::~ScreenDemoNameEnemy() = default;
ScreenShopBG::~ScreenShopBG() = default;
ScreenShopBtnList5::~ScreenShopBtnList5() = default;
ScreenShopHorse::~ScreenShopHorse() = default;
ScreenPauseMenuBG::~ScreenPauseMenuBG() = default;
ScreenSeekPadMenuBG::~ScreenSeekPadMenuBG() = default;
ScreenMainScreenMS::~ScreenMainScreenMS() = default;
ScreenMainScreenHeartIchigekiDLC::~ScreenMainScreenHeartIchigekiDLC() = default;
ScreenAppSystemWindowNoBtn::~ScreenAppSystemWindowNoBtn() = default;
ScreenGameOver::~ScreenGameOver() = default;
ScreenMessageTipsPauseMenu::~ScreenMessageTipsPauseMenu() = default;
ScreenAmiiboWindow::~ScreenAmiiboWindow() = default;
ScreenSystemWindowNoBtn::~ScreenSystemWindowNoBtn() = default;
ScreenSystemWindow00::~ScreenSystemWindow00() = default;
ScreenPauseMenuMantan::~ScreenPauseMenuMantan() = default;
ScreenPauseMenuEiketsu::~ScreenPauseMenuEiketsu() = default;
ScreenAppSystemWindow::~ScreenAppSystemWindow() = default;
ScreenHardModeTextDLC::~ScreenHardModeTextDLC() = default;
ScreenEnd::~ScreenEnd() = default;
ScreenLastComplete::~ScreenLastComplete() = default;
ScreenOPtext::~ScreenOPtext() = default;
ScreenLoadingWeapon::~ScreenLoadingWeapon() = default;
ScreenMainHardMode::~ScreenMainHardMode() = default;
ScreenSkip::~ScreenSkip() = default;
ScreenChangeController::~ScreenChangeController() = default;
ScreenDemoStart::~ScreenDemoStart() = default;
ScreenBootUp::~ScreenBootUp() = default;
ScreenAppMenuBtn::~ScreenAppMenuBtn() = default;
ScreenHomeMenuCapture::~ScreenHomeMenuCapture() = default;

}  // namespace uking::ui
