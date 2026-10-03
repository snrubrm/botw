#include "Game/AI/Action/actionPlayerHoldUpDRC.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerHoldUpDRC::PlayerHoldUpDRC(const InitArg& arg) : PlayerAction(arg) {}

PlayerHoldUpDRC::~PlayerHoldUpDRC() = default;

void PlayerHoldUpDRC::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x1);
    static_cast<ksys::act::Player*>(mActor)->_cf8.set(0x2);
    const bool riding = static_cast<ksys::act::Player*>(mActor)->isRidingHorse();
    auto* player = static_cast<ksys::act::Player*>(mActor);
    if (riding)
        player->x_23(mASName_d.cstr(), false, -1.0f);
    else
        player->switchToAnimSequenceMaybe(mASName_d.cstr(), true, -1.0f);
    static_cast<ksys::act::Player*>(mActor)->_1800 = 0;
}

void PlayerHoldUpDRC::leave_() {}

void PlayerHoldUpDRC::loadParams_() {
    getDynamicParam(&mIsContinued_d, "IsContinued");
    getDynamicParam(&mASName_d, "ASName");
}

void PlayerHoldUpDRC::calc_() {
    PlayerAction::calc_();
}

bool PlayerHoldUpDRC::isChangeable() const {
    return false;
}

}  // namespace uking::action
