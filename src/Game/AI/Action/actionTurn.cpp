#include "Game/AI/Action/actionTurn.h"

namespace uking::action {

Turn::Turn(const InitArg& arg) : TurnBase(arg) {}

void Turn::enter_(ksys::act::ai::InlineParamPack* params) {
    TurnBase::enter_(params);
    playAS("Turn", true, 0, 0, -1.0f);
}

}  // namespace uking::action
