#include "Game/AI/Action/actionGuardianAimBeam.h"

namespace uking::action {

// NON_MATCHING: order of the zero stores to the parameter pointers
GuardianAimBeam::GuardianAimBeam(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GuardianAimBeam::~GuardianAimBeam() = default;

bool GuardianAimBeam::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GuardianAimBeam::enter_(ksys::act::ai::InlineParamPack* params) {
    m32("");
}

void GuardianAimBeam::leave_() {
    _68.sub_71006F2D08();
}

void GuardianAimBeam::loadParams_() {
    getStaticParam(&mParams.mTargetOffset_s, "TargetOffset");
    getStaticParam(&mParams.mTargetOffsetY_s, "TargetOffsetY");
    getStaticParam(&mParams.mFluctuationRange_s, "FluctuationRange");
    getStaticParam(&mParams.mFluctuationTime_s, "FluctuationTime");
    getStaticParam(&mParams.mFluctuationSpan_s, "FluctuationSpan");
    getStaticParam(&mParams.mNodeName_s, "NodeName");
    getStaticParam(&mParams.mNodeOffset_s, "NodeOffset");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
}

void GuardianAimBeam::calc_() {
    if (_68._f4 <= _68._d8) {
        _68.end("Target_End");
        setFinished();
        return;
    }
    _68.update(*mParams.mTargetPos_d);
}

void GuardianAimBeam::m32(const char* name) {
    _68.init(mActor, "Target", "Laser", name, "BeamSightSearch", "BeamSightLocking",
             "BeamSightLocked", *mParams.mFluctuationRange_s, *mParams.mFluctuationSpan_s, *mParams.mFluctuationTime_s,
             *mParams.mTargetOffsetY_s, *mParams.mTargetPos_d, mParams.mNodeName_s, *mParams.mNodeOffset_s);
    _68._f4 = m33();
}

f32 GuardianAimBeam::m33() {
    return 150.0f;
}

}  // namespace uking::action
