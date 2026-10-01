#include "Game/AI/Action/actionBattleWalk.h"

namespace uking::action {

BattleWalk::BattleWalk(const InitArg& arg) : MoveBase(arg) {}

void BattleWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS("BattleWalk", false, 0, 0, -1.0f);
    MoveBase::enter_(params);
}

}  // namespace uking::action
