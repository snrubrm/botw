#include "Game/AI/Action/actionGuardianMiniGuardBattleWalk.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

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

void GuardianMiniGuardBattleWalk::sub_7100195260() {
    auto* list = mActor->getASList();
    if (!list)
        return;
    for (int i = 0; i < 3; ++i) {
        if (*mASSlot_s == i)
            list->sub_710115B140(sead::SafeString(mASName_s.cstr()), i, i, 0, 0);
        else
            playAS("BattleWalk", true, i, 0, -1.0f);
    }
}

}  // namespace uking::action
