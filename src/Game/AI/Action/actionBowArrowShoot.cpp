#include "Game/AI/Action/actionBowArrowShoot.h"

namespace uking::action {

BowArrowShoot::BowArrowShoot(const InitArg& arg) : BindAction(arg) {}

void BowArrowShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    BindAction::enter_(params);
}

void BowArrowShoot::calc_() {
    BindAction::calc_();
    if (isFinishedAS(0, 0))
        setFinished();
}

}  // namespace uking::action
