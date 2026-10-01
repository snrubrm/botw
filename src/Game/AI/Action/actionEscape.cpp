#include "Game/AI/Action/actionEscape.h"

namespace uking::action {

Escape::Escape(const InitArg& arg) : MoveBase(arg) {}

void Escape::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveBase::enter_(params);
    playAS("Escape", true, 0, 0, -1.0f);
}

}  // namespace uking::action
