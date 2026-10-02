#include "Game/AI/Action/actionSetTgIgnoreObstacle.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::action {

SetTgIgnoreObstacle::SetTgIgnoreObstacle(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetTgIgnoreObstacle::~SetTgIgnoreObstacle() = default;

bool SetTgIgnoreObstacle::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetTgIgnoreObstacle::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71007A458C(mActor, true);
}

void SetTgIgnoreObstacle::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetTgIgnoreObstacle::loadParams_() {}

void SetTgIgnoreObstacle::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
