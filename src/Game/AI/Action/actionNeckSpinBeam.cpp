#include "Game/AI/Action/actionNeckSpinBeam.h"

namespace uking::action {

NeckSpinBeam::NeckSpinBeam(const InitArg& arg) : NeckSpin(arg) {}


bool NeckSpinBeam::init_(sead::Heap* heap) {
    return NeckSpin::init_(heap);
}

void NeckSpinBeam::enter_(ksys::act::ai::InlineParamPack* params) {
    NeckSpin::enter_(params);
}

void NeckSpinBeam::leave_() {
    _b8.sub_71006F3B14(false);
    NeckSpin::leave_();
}

void NeckSpinBeam::loadParams_() {
    NeckSpin::loadParams_();
    getStaticParam(&mBeamRange_s, "BeamRange");
    getStaticParam(&mBeamBoneName_s, "BeamBoneName");
    getStaticParam(&mBeamActorKey_s, "BeamActorKey");
    getStaticParam(&mBeamActorName_s, "BeamActorName");
    getStaticParam(&mMuzzleOffset_s, "MuzzleOffset");
    getStaticParam(&mBeamDirection_s, "BeamDirection");
    getMapUnitParam(&mBeamRange_m, "BeamRange");
}

void NeckSpinBeam::calc_() {
    NeckSpin::calc_();
    _b8.sub_71006F3A6C();
}

}  // namespace uking::action
