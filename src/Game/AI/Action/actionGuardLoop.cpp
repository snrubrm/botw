#include "Game/AI/Action/actionGuardLoop.h"

namespace uking::action {

GuardLoop::GuardLoop(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

void GuardLoop::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
    playAS("Guard", false, 0, 0, -1.0f);
}

}  // namespace uking::action
