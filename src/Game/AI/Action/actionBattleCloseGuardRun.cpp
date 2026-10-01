#include "Game/AI/Action/actionBattleCloseGuardRun.h"

namespace uking::action {

BattleCloseGuardRun::BattleCloseGuardRun(const InitArg& arg) : BattleCloseMoveAction(arg) {}

BattleCloseGuardRun::~BattleCloseGuardRun() = default;

void BattleCloseGuardRun::enter_(ksys::act::ai::InlineParamPack* params) {
    BattleCloseMoveAction::enter_(params);
    playAS("GuardRun", true, 0, 0, -1.0f);
}

}  // namespace uking::action
