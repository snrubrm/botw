#include "Game/AI/Action/actionPriestBossAimBeamWithAS.h"

namespace uking::action {

PriestBossAimBeamWithAS::PriestBossAimBeamWithAS(const InitArg& arg) : PriestBossAimBeam(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
PriestBossAimBeamWithAS::~PriestBossAimBeamWithAS() {
    ;
}

bool PriestBossAimBeamWithAS::init_(sead::Heap* heap) {
    return PriestBossAimBeam::init_(heap);
}

void PriestBossAimBeamWithAS::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossAimBeam::enter_(params);
}

void PriestBossAimBeamWithAS::leave_() {
    PriestBossAimBeam::leave_();
}

void PriestBossAimBeamWithAS::loadParams_() {
    PriestBossAimBeam::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void PriestBossAimBeamWithAS::calc_() {
    PriestBossAimBeam::calc_();
}

}  // namespace uking::action
