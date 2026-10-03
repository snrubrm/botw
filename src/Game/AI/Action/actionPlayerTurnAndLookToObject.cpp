#include "Game/AI/Action/actionPlayerTurnAndLookToObject.h"

namespace uking::action {

PlayerTurnAndLookToObject::PlayerTurnAndLookToObject(const InitArg& arg)
    : PlayerLookAtObject(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
PlayerTurnAndLookToObject::~PlayerTurnAndLookToObject() {
    ;
}

bool PlayerTurnAndLookToObject::init_(sead::Heap* heap) {
    return PlayerLookAtObject::init_(heap);
}

void PlayerTurnAndLookToObject::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerLookAtObject::enter_(params);
}

void PlayerTurnAndLookToObject::leave_() {
    PlayerLookAtObject::leave_();
}

void PlayerTurnAndLookToObject::loadParams_() {
    PlayerLookAtObject::loadParams_();
    getDynamicParam(&mIsUseSlowTurn_d, "IsUseSlowTurn");
    getDynamicParam(&mIsTurnToLookAtPos_d, "IsTurnToLookAtPos");
}

void PlayerTurnAndLookToObject::calc_() {
    PlayerLookAtObject::calc_();
}

bool PlayerTurnAndLookToObject::isChangeable() const {
    return false;
}

}  // namespace uking::action
