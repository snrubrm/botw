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
    getStaticParam(&mTargetOffset_s, "TargetOffset");
    getStaticParam(&mTargetOffsetY_s, "TargetOffsetY");
    getStaticParam(&mFluctuationRange_s, "FluctuationRange");
    getStaticParam(&mFluctuationTime_s, "FluctuationTime");
    getStaticParam(&mFluctuationSpan_s, "FluctuationSpan");
    getStaticParam(&mNodeName_s, "NodeName");
    getStaticParam(&mNodeOffset_s, "NodeOffset");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void GuardianAimBeam::calc_() {
    if (_68._f4 <= _68._d8) {
        _68.end("Target_End");
        setFinished();
        return;
    }
    _68.update(*mTargetPos_d);
}

void GuardianAimBeam::m32(const char* name) {
    _68.init(mActor, "Target", "Laser", name, "BeamSightSearch", "BeamSightLocking",
             "BeamSightLocked", *mFluctuationRange_s, *mFluctuationSpan_s, *mFluctuationTime_s,
             *mTargetOffsetY_s, *mTargetPos_d, mNodeName_s, *mNodeOffset_s);
    _68._f4 = m33();
}

f32 GuardianAimBeam::m33() {
    return 150.0f;
}

}  // namespace uking::action
