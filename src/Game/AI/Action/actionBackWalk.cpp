#include "Game/AI/Action/actionBackWalk.h"

namespace uking::action {

BackWalk::BackWalk(const InitArg& arg) : BackWalkEx(arg) {}

void BackWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS("BackWalk", true, 0, 0, -1.0f);
    BackWalkEx::enter_(params);
}

}  // namespace uking::action
