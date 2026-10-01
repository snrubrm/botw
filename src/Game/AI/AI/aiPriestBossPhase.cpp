#include "Game/AI/AI/aiPriestBossPhase.h"

namespace uking::ai {

PriestBossPhase::PriestBossPhase(const InitArg& arg) : PriestBossMeta(arg) {}

PriestBossPhase::~PriestBossPhase() = default;

bool PriestBossPhase::init_(sead::Heap* heap) {
    return PriestBossMeta::init_(heap);
}

void PriestBossPhase::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossMeta::enter_(params);
}

void PriestBossPhase::leave_() {
    PriestBossMeta::leave_();
    _60.resetBit(Flag(Flag::_4));
}

void PriestBossPhase::loadParams_() {
    PriestBossMeta::loadParams_();
    getStaticParam(&mPercentLifeTransition_s, "PercentLifeTransition");
    getStaticParam(&mPercentLifePrevious_s, "PercentLifePrevious");
}

bool PriestBossPhase::m36() {
    return *mMetaAILife_a <= int(float(*mMetaAIMaxLife_a) * *mPercentLifeTransition_s);
}

}  // namespace uking::ai
