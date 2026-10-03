#include "Game/AI/Action/actionPlayerWakeBoard.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

PlayerWakeBoard::PlayerWakeBoard(const InitArg& arg) : PlayerAction(arg) {}

void PlayerWakeBoard::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerWakeBoard::leave_() {
    PlayerAction::leave_();
}

void PlayerWakeBoard::loadParams_() {}

bool PlayerWakeBoard::handleMessage_(const ksys::Message& message) {
    const auto type = message.getType();
    if (type == 0x8000025 || type == 0x8000026) {
        _1d = true;
        return true;
    }
    return false;
}

void PlayerWakeBoard::calc_() {
    PlayerAction::calc_();
}

bool PlayerWakeBoard::isChangeable() const {
    return false;
}

}  // namespace uking::action
