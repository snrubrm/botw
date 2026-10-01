#include "Game/AI/Action/actionRun.h"

namespace uking::action {

Run::Run(const InitArg& arg) : MoveBase(arg) {}

void Run::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveBase::enter_(params);
    playAS("Run", true, 0, 0, -1.0f);
}

}  // namespace uking::action
