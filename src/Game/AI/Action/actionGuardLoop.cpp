#include "Game/AI/Action/actionGuardLoop.h"

namespace uking::action {

GuardLoop::GuardLoop(const InitArg& arg) : StopBase(arg) {}

void GuardLoop::enter_(ksys::act::ai::InlineParamPack* params) {
    StopBase::enter_(params);
    playAS("Guard", false, 0, 0, -1.0f);
}

}  // namespace uking::action
