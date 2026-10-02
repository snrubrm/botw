#include "Game/AI/Action/actionGuardianAimBeamWithAS.h"
#include "Game/AI/aiUnk_71005D6D10.h"

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
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    _178 = false;
    if (*mIsChangeable_s)
        mFlags.set(Flag::Changeable);
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
    if (_178) {
        GuardianAimBeam::calc_();
        return;
    }
    m32("Aim");
}

void GuardianAimBeamWithAS::m32(const char* name) {
    if (sub_71005DD780(mActor, 59, nullptr, 0, 0)) {
        GuardianAimBeam::m32(name);
        _178 = true;
    }
}

f32 GuardianAimBeamWithAS::m33() {
    return *mFluctuationTime_s;
}

}  // namespace uking::action
