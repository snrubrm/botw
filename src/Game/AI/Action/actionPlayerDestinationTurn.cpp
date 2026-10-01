#include "Game/AI/Action/actionPlayerDestinationTurn.h"

namespace uking::action {

PlayerDestinationTurn::PlayerDestinationTurn(const InitArg& arg) : PlayerAction(arg) {}

void PlayerDestinationTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerDestinationTurn::leave_() {}

void PlayerDestinationTurn::loadParams_() {
    getDynamicParam(&mDestPosX_d, "DestPosX");
    getDynamicParam(&mDestPosY_d, "DestPosY");
    getDynamicParam(&mDestPosZ_d, "DestPosZ");
}

void PlayerDestinationTurn::calc_() {
    PlayerAction::calc_();
}

bool PlayerDestinationTurn::isChangeable() const {
    return false;
}

bool PlayerDestinationTurn::m34() {
    return true;
}

bool PlayerDestinationTurn::m35() {
    return true;
}

}  // namespace uking::action
