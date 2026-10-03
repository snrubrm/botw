#include "Game/AI/Action/actionPlayerClimbRest.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

PlayerClimbRest::PlayerClimbRest(const InitArg& arg) : PlayerAction(arg) {}

PlayerClimbRest::~PlayerClimbRest() = default;

void PlayerClimbRest::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerClimbRest::leave_() {
    PlayerAction::leave_();
}

void PlayerClimbRest::loadParams_() {
    getStaticParam(&mEnergyClimb_s, "EnergyClimb");
}

void PlayerClimbRest::calc_() {
    PlayerAction::calc_();
}

bool PlayerClimbRest::handleMessage_(const ksys::Message* message) {
    return message->getType() == 0x7800005;
}

bool PlayerClimbRest::isChangeable() const {
    return false;
}

}  // namespace uking::action
