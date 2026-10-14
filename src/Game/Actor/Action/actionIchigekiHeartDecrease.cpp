#include "Game/Actor/Action/actionIchigekiHeartDecrease.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUnkSingletons.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

IchigekiHeartDecrease::IchigekiHeartDecrease(const InitArg& arg) : ksys::act::ai::Action(arg) {}

IchigekiHeartDecrease::~IchigekiHeartDecrease() = default;

bool IchigekiHeartDecrease::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void IchigekiHeartDecrease::enter_(ksys::act::ai::InlineParamPack* params) {
    _30 = 0;
    _34 = act::PlayerInfo::instance()->getLifeFromPlayerActor();
    auto* hearts = ui::Unk_71025d6578::instance();
    if (hearts->_34 != 0) {
        _34 = _38 = hearts->_30 - hearts->_34;
        act::PlayerInfo::instance()->mPlayerActor->m324(0);
    }

    auto* screen = sead::DynamicCast<ui::ScreenMainScreenHeartIchigekiDLC>(
        eui::ScreenMgr::instance()->getScreen(ui::ScreenId::MainScreenHeartIchigekiDLC));
    if (screen) {
        if (screen->isOpened())
            return;
    } else {
        ui::createAndLoadScreenIfNeededImpl(36, nullptr);
        screen = sead::DynamicCast<ui::ScreenMainScreenHeartIchigekiDLC>(
            eui::ScreenMgr::instance()->getScreen(ui::ScreenId::MainScreenHeartIchigekiDLC));
        if (!screen)
            return;
    }
    screen->open(1);
}

void IchigekiHeartDecrease::leave_() {
    if (auto* info = uking::act::PlayerInfo::instance())
        info->setLifeForPlayerActor(1);
}

void IchigekiHeartDecrease::loadParams_() {
    getDynamicParam(&mUseFrame_d, "UseFrame");
    getDynamicParam(&mIsUseConstSpeed_d, "IsUseConstSpeed");
}

void IchigekiHeartDecrease::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
