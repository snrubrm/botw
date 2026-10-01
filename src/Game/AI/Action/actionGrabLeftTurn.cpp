#include "Game/AI/Action/actionGrabLeftTurn.h"

namespace uking::action {

GrabLeftTurn::GrabLeftTurn(const InitArg& arg) : TurnBase(arg) {}

void GrabLeftTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    TurnBase::enter_(params);
    playAS("GrabLeftTurn", false, 0, 0, -1.0f);
}

}  // namespace uking::action
