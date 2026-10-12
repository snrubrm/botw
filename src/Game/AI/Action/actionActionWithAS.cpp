#include "Game/AI/Action/actionActionWithAS.h"

namespace uking::action {

ActionWithAS::ActionWithAS(const InitArg& arg) : StopBase(arg) {}

void ActionWithAS::enter_(ksys::act::ai::InlineParamPack* params) {
    StopBase::enter_(params);
    mFlags.reset(Flag::Changeable);
}

void ActionWithAS::calc_() {
    StopBase::calc_();
    if (isFinishedAS(0, 0))
        setFinished();
}

}  // namespace uking::action
