#include "Game/AI/AI/aiPriestBossActorPhaseSecondStart.h"
#include "Game/AI/aiUnk_710071E0D8.h"

namespace uking::ai {

PriestBossActorPhaseSecondStart::PriestBossActorPhaseSecondStart(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

PriestBossActorPhaseSecondStart::~PriestBossActorPhaseSecondStart() = default;

bool PriestBossActorPhaseSecondStart::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PriestBossActorPhaseSecondStart::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710050E7E0();
}

void PriestBossActorPhaseSecondStart::calc_() {
    if (isCurrentChild("共通")) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed()) {
            actSetVisible(true, mActor);
            setFinished();
        }
    } else {
        sub_710050E7E0();
    }
}

void PriestBossActorPhaseSecondStart::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PriestBossActorPhaseSecondStart::loadParams_() {
    getAITreeVariable(&mEquipWeaponBufIndex_a, "EquipWeaponBufIndex");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

}  // namespace uking::ai
