#include "Game/AI/Action/actionAppear.h"

namespace uking::action {

Appear::Appear(const InitArg& arg) : ActionWithAS(arg) {}

void Appear::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS("Appear", false, 0, 0, -1.0f);
}

}  // namespace uking::action
