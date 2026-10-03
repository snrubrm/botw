#include "Game/AI/AI/aiPriestBossBlowoffDamageSelect.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

PriestBossBlowoffDamageSelect::PriestBossBlowoffDamageSelect(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
PriestBossBlowoffDamageSelect::~PriestBossBlowoffDamageSelect() {
    ;
}

bool PriestBossBlowoffDamageSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PriestBossBlowoffDamageSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* base = mActor->getDamageMgr()) {
        _38 = base->getField54();
        _3c = base->getField50();
        if (auto* mgr = sead::DynamicCast<uking::dmg::DamageManagerBase>(base)) {
            auto* attacker = mgr->getAttacker();
            if (attacker->hasProc()) {
                ksys::act::ActorConstDataAccess accessor;
                ksys::act::acquireActor(attacker, &accessor);
                if (accessor.hasProc())
                    _40 = accessor.getName();
            }
        }
    }
    changeChild("リアクション準備");
}

void PriestBossBlowoffDamageSelect::calc_() {
    if (!getCurrentChild()->isFinished())
        return;

    if (isCurrentChild("リアクション準備"))
        sub_7100510A94();
    else
        setFinished();
}

void PriestBossBlowoffDamageSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PriestBossBlowoffDamageSelect::loadParams_() {}

}  // namespace uking::ai
