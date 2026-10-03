#include "Game/AI/Action/actionPlayerTurnAndLookToObjectNow.h"

namespace uking::action {

PlayerTurnAndLookToObjectNow::PlayerTurnAndLookToObjectNow(const InitArg& arg)
    : PlayerLookAtObjectNow(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
PlayerTurnAndLookToObjectNow::~PlayerTurnAndLookToObjectNow() {
    ;
}

bool PlayerTurnAndLookToObjectNow::init_(sead::Heap* heap) {
    return PlayerLookAtObjectNow::init_(heap);
}

void PlayerTurnAndLookToObjectNow::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerLookAtObjectNow::enter_(params);
}

void PlayerTurnAndLookToObjectNow::leave_() {
    PlayerLookAtObjectNow::leave_();
}

void PlayerTurnAndLookToObjectNow::loadParams_() {
    PlayerLookAtObjectNow::loadParams_();
}

void PlayerTurnAndLookToObjectNow::calc_() {
    PlayerLookAtObjectNow::calc_();
}

}  // namespace uking::action
