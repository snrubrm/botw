#include "Game/AI/Action/actionBattleCloseMeanderGuardRun.h"

namespace uking::action {

BattleCloseMeanderGuardRun::BattleCloseMeanderGuardRun(const InitArg& arg)
    : BattleCloseMeanderRun(arg) {}

BattleCloseMeanderGuardRun::~BattleCloseMeanderGuardRun() = default;

void BattleCloseMeanderGuardRun::m40() {
    playAS("GuardRun", true, 0, 0, -1.0f);
}

}  // namespace uking::action
