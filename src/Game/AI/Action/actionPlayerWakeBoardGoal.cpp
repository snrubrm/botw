#include "Game/AI/Action/actionPlayerWakeBoardGoal.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::action {

PlayerWakeBoardGoal::PlayerWakeBoardGoal(const InitArg& arg) : PlayerAction(arg) {}

PlayerWakeBoardGoal::~PlayerWakeBoardGoal() = default;

void PlayerWakeBoardGoal::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerWakeBoardGoal::leave_() {
    auto* as_list = mActor->getASList();
    if (as_list && as_list->_163 & 2)
        as_list->sub_710115C11C();
}

void PlayerWakeBoardGoal::loadParams_() {
    getDynamicParam(&mASName_d, "ASName");
}

void PlayerWakeBoardGoal::calc_() {
    PlayerAction::calc_();
}

bool PlayerWakeBoardGoal::isChangeable() const {
    return false;
}

}  // namespace uking::action
