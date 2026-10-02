#include "Game/AI/Action/actionPlayerWakeBoardGoal.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::action {

PlayerWakeBoardGoal::PlayerWakeBoardGoal(const InitArg& arg) : PlayerAction(arg) {}

PlayerWakeBoardGoal::~PlayerWakeBoardGoal() = default;

void PlayerWakeBoardGoal::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x800000);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x20000);
    mActor->getASList()->sub_710115BC28(mASName_d.cstr(), -1.0f);
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
