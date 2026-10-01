#include "Game/AI/Action/actionActionWithAS.h"

namespace uking::action {

ActionWithAS::ActionWithAS(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

void ActionWithAS::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
    mFlags.reset(Flag::Changeable);
}

void ActionWithAS::calc_() {
    ActionWithPosAngReduce::calc_();
    if (isFinishedAS(0, 0))
        setFinished();
}

bool ActionWithAS::isFinished() const {
    return mFlags.isOn(Flag::Finished) || isFinishedAS(0, 0);
}

}  // namespace uking::action
