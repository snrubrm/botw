#include "Game/AI/Action/actionPriestBossAimBeamWithAS.h"
#include "Game/AI/aiUnk_71005D6D10.h"

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
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    _1a0 = false;
}

void PriestBossAimBeamWithAS::leave_() {
    PriestBossAimBeam::leave_();
}

void PriestBossAimBeamWithAS::loadParams_() {
    PriestBossAimBeam::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void PriestBossAimBeamWithAS::calc_() {
    if (_1a0) {
        PriestBossAimBeam::calc_();
        return;
    }
    m32("Aim");
}

void PriestBossAimBeamWithAS::m32(const char* name) {
    if (sub_71005DD780(mActor, 59, nullptr, 0, 0)) {
        PriestBossAimBeam::m32(name);
        _1a0 = true;
    }
}

}  // namespace uking::action
