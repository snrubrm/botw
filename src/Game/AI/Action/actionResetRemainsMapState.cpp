#include "Game/AI/Action/actionResetRemainsMapState.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

ResetRemainsMapState::ResetRemainsMapState(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ResetRemainsMapState::~ResetRemainsMapState() = default;

bool ResetRemainsMapState::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool ResetRemainsMapState::oneShot_() {
    ui::sub_7100A9D748();
    return ksys::act::ai::Action::oneShot_();
}

void ResetRemainsMapState::loadParams_() {}

}  // namespace uking::action
