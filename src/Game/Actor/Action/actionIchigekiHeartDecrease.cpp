#include "Game/Actor/Action/actionIchigekiHeartDecrease.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUnkSingletons.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/System/VFR.h"

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

// NON_MATCHING: scheduling / the `life % 4 == 0 && _38 != life` test is a ccmp chain in the original.
void IchigekiHeartDecrease::calc_() {
    if (isFinished() || isFailed())
        return;

    const auto update_life = [this](s32 life) {
        auto* info = act::PlayerInfo::instance();
        if (!info)
            return;
        info->setLifeForPlayerActor(life);
        if (life % 4 == 0 && _38 != life && _30 != 0.0f) {
            auto* screen = sead::DynamicCast<ui::ScreenMainScreenHeartIchigekiDLC>(
                eui::ScreenMgr::instance()->getScreen(ui::ScreenId::MainScreenHeartIchigekiDLC));
            if (screen) {
                if (life >= 5) {
                    screen->invokeSoundLink2Event_("mc_HeartDown");
                } else if (life == 4) {
                    screen->sub_7100A16ADC();
                    ui::playSound("mc_HeartAlert_L", nullptr);
                    ui::Unk_71025d6578::instance()->_3a = 1;
                }
            }
        }
        _38 = life;
    };

    switch (*mIsUseConstSpeed_d) {
    case 0: {
        s32 life = sead::Mathf::ceil(_34 + _30 * (-119.0f / *mUseFrame_d));
        if (life < 1)
            life = 1;
        update_life(life);
        break;
    }
    case 1:
        update_life(sead::Mathf::ceil(_34 - _30 * ((_34 - 1.0f) / *mUseFrame_d)));
        break;
    }

    if (_30 >= *mUseFrame_d) {
        setFinished();
        mFlags.set(Flag::Changeable);
    }
    _30 += ksys::VFR::instance()->getDeltaTime();
}

}  // namespace uking::action
