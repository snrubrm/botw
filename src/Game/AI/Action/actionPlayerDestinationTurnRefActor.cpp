#include "Game/AI/Action/actionPlayerDestinationTurnRefActor.h"

namespace uking::action {

PlayerDestinationTurnRefActor::PlayerDestinationTurnRefActor(const InitArg& arg)
    : PlayerAction(arg) {}

PlayerDestinationTurnRefActor::~PlayerDestinationTurnRefActor() = default;

void PlayerDestinationTurnRefActor::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerDestinationTurnRefActor::leave_() {}

void PlayerDestinationTurnRefActor::loadParams_() {
    getDynamicParam(&mUniqName_d, "UniqName");
}

void PlayerDestinationTurnRefActor::calc_() {
    PlayerAction::calc_();
}

bool PlayerDestinationTurnRefActor::isChangeable() const {
    return false;
}

bool PlayerDestinationTurnRefActor::m34() {
    return true;
}

bool PlayerDestinationTurnRefActor::m35() {
    return true;
}

}  // namespace uking::action
