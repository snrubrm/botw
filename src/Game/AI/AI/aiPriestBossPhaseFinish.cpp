#include "Game/AI/AI/aiPriestBossPhaseFinish.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::ai {

PriestBossPhaseFinish::PriestBossPhaseFinish(const InitArg& arg) : PriestBossPhase(arg) {}

PriestBossPhaseFinish::~PriestBossPhaseFinish() = default;

bool PriestBossPhaseFinish::init_(sead::Heap* heap) {
    return PriestBossPhase::init_(heap);
}

void PriestBossPhaseFinish::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossPhase::enter_(params);
}

void PriestBossPhaseFinish::calc_() {
    if (isFinished() || isFailed())
        return;

    _90.update();
    if (_90.value <= sead::Mathf::epsilon()) {
        if (ksys::gdt::getFlag_Defeated_Priest_Boss_Normal_Num() == 0)
            ksys::gdt::increaseFlag_FamouseValue(1);
        mActor->emitBasicSigOn();
        setFinished();
        return;
    }

    if (_90.value <= 5.0f && !_9c) {
        sub_7100529AB0();
        _9c = true;
    }
}

void PriestBossPhaseFinish::leave_() {
    PriestBossPhase::leave_();
}

void PriestBossPhaseFinish::loadParams_() {
    PriestBossPhase::loadParams_();
    getStaticParam(&mStartDemoDelayFrames_s, "StartDemoDelayFrames");
    getMapUnitParam(&mPriestBossStartPhase_m, "PriestBossStartPhase");
}

}  // namespace uking::ai
