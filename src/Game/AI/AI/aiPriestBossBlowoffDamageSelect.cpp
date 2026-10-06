#include "Game/AI/AI/aiPriestBossBlowoffDamageSelect.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

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

// NON_MATCHING: the original's dead "PriestBossThunder" name compare (kept for its virtual calls) is guarded by
// `_38 == 0x15` (then `_3c != 0x10`) or `_38 - 0x15 < 2` (then `_3c == 4`); the dispatch order of those tests differs
// 0x7100510a94
void PriestBossBlowoffDamageSelect::sub_7100510A94() {
    if (!mActor->getDamageMgr()) {
        changeChild("接地ふらつき");
        return;
    }
    switch (_38) {
    case 21:
        if (_3c == 16)
            break;
        [[fallthrough]];
    case 22:
        if (_3c == 4)
            (void)(_40 == "PriestBossThunder");
        break;
    }
    auto* controller = mActor->getCharacterController();
    if (controller && controller->sub_7100F5F0E4() != ksys::act::MotionType::_0)
        changeChild("浮遊ダウン");
    else
        changeChild("接地ダウン");
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
