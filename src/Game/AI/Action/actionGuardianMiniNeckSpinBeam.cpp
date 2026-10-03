#include "Game/AI/Action/actionGuardianMiniNeckSpinBeam.h"

namespace uking::action {

GuardianMiniNeckSpinBeam::GuardianMiniNeckSpinBeam(const InitArg& arg) : NeckSpinBeam(arg) {}

GuardianMiniNeckSpinBeam::~GuardianMiniNeckSpinBeam() = default;

void GuardianMiniNeckSpinBeam::enter_(ksys::act::ai::InlineParamPack* params) {
    NeckSpinBeam::enter_(params);
}

void GuardianMiniNeckSpinBeam::loadParams_() {
    NeckSpinBeam::loadParams_();
    getStaticParam(&mSpinNum_s, "SpinNum");
    getStaticParam(&mMaxLengthTime_s, "MaxLengthTime");
    getStaticParam(&mIsStraight_s, "IsStraight");
}

void GuardianMiniNeckSpinBeam::calc_() {
    NeckSpinBeam::calc_();
}

void GuardianMiniNeckSpinBeam::m33() {
    const f32 speed = *mSpinSpeed_s;
    if (speed <= sead::Mathf::epsilon() && speed >= -sead::Mathf::epsilon())
        return;
    NeckSpin::m33();
}

}  // namespace uking::action
