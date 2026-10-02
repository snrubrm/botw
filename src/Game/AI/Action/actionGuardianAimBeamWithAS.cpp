#include "Game/AI/Action/actionGuardianAimBeamWithAS.h"

namespace uking::action {

GuardianAimBeamWithAS::GuardianAimBeamWithAS(const InitArg& arg) : GuardianAimBeam(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
GuardianAimBeamWithAS::~GuardianAimBeamWithAS() {
    ;
}

bool GuardianAimBeamWithAS::init_(sead::Heap* heap) {
    return GuardianAimBeam::init_(heap);
}

void GuardianAimBeamWithAS::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianAimBeam::enter_(params);
}

void GuardianAimBeamWithAS::leave_() {
    GuardianAimBeam::leave_();
}

void GuardianAimBeamWithAS::loadParams_() {
    GuardianAimBeam::loadParams_();
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mASName_s, "ASName");
}

void GuardianAimBeamWithAS::calc_() {
    GuardianAimBeam::calc_();
}

}  // namespace uking::action
