#include "Game/AI/Action/actionGuardianMiniGuardBattleWalk.h"

namespace uking::action {

GuardianMiniGuardBattleWalk::GuardianMiniGuardBattleWalk(const InitArg& arg)
    : BattleCloseWalk(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
GuardianMiniGuardBattleWalk::~GuardianMiniGuardBattleWalk() {
    ;
}

void GuardianMiniGuardBattleWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    BattleCloseWalk::enter_(params);
    sub_7100195260();
}

void GuardianMiniGuardBattleWalk::loadParams_() {
    BattleCloseWalk::loadParams_();
    getStaticParam(&mASSlot_s, "ASSlot");
    getStaticParam(&mASName_s, "ASName");
}

}  // namespace uking::action
