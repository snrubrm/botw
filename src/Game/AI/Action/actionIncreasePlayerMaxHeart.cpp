#include "Game/AI/Action/actionIncreasePlayerMaxHeart.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::ui {
// uiManagerFacade.cpp / uiMiscFacade.cpp
void updateLifeAndMaxLife(s32 life, s32 max_life);
void sub_7100A94B90();
}  // namespace uking::ui

namespace uking::action {

IncreasePlayerMaxHeart::IncreasePlayerMaxHeart(const InitArg& arg) : ksys::act::ai::Action(arg) {}

IncreasePlayerMaxHeart::~IncreasePlayerMaxHeart() = default;

bool IncreasePlayerMaxHeart::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void IncreasePlayerMaxHeart::enter_(ksys::act::ai::InlineParamPack* params) {
    using ksys::act::PlayerInfo;
    _30 = 0;
    if (!PlayerInfo::instance()) {
        setFailed();
        return;
    }

    const s32 max_hearts = PlayerInfo::instance()->getMaxHeartValue() + *mValue_d * 4;
    PlayerInfo::instance()->setMaxHeartValue(max_hearts);
    const s32 life = PlayerInfo::instance()->getLifeFromPlayerActor();
    if (auto* player = PlayerInfo::instance()->getPlayer()) {
        if (auto* link = player->m129())
            link->m377();
    }

    auto* info = PlayerInfo::instance();
    if (*mValue_d >= 1) {
        info->setLifeForPlayerActor(info->getMaxLifeFromPlayerActor());
    } else if (info->getLifeFromPlayerActor() > life) {
        PlayerInfo::instance()->setLifeForPlayerActor(life);
    }

    ui::sub_7100A94AF0();
    if (*mIsMoveCenter_d)
        ui::sub_7100A94B90();
    ui::updateLifeAndMaxLife(PlayerInfo::instance()->getLifeFromPlayerActor(),
                             PlayerInfo::instance()->getMaxLifeFromPlayerActor());
}

void IncreasePlayerMaxHeart::leave_() {
    ksys::act::ai::Action::leave_();
}

void IncreasePlayerMaxHeart::loadParams_() {
    getDynamicParam(&mValue_d, "Value");
    getDynamicParam(&mIsMoveCenter_d, "IsMoveCenter");
}

void IncreasePlayerMaxHeart::calc_() {
    if (isFinished() || isFailed())
        return;
    switch (_30) {
    case 0:
        ui::sub_7100A94B70(true);
        _30 = 1;
        break;
    case 1:
        ui::sub_7100A94B08();
        _30 = 2;
        break;
    case 2:
        if (!ui::sub_7100A94AC8()) {
            setFinished();
            _30 = 3;
        }
        break;
    case 3:
        break;
    default:
        setFailed();
        break;
    }
}

}  // namespace uking::action
