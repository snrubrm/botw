#include "Game/AI/Action/actionNeckSpinBeam.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

NeckSpinBeam::NeckSpinBeam(const InitArg& arg) : NeckSpin(arg) {}


bool NeckSpinBeam::init_(sead::Heap* heap) {
    if (!NeckSpin::init_(heap))
        return false;
    _b8.sub_71006F331C(heap, m34(), m35(), mBeamBoneName_s,
                       *mBeamRange_m > 0.0f ? *mBeamRange_m : *mBeamRange_s, 1.0f, mMuzzleOffset_s,
                       mBeamDirection_s, m36());
    return true;
}

void NeckSpinBeam::enter_(ksys::act::ai::InlineParamPack* params) {
    NeckSpin::enter_(params);
    mFlags.set(Flag::Changeable);
    _b8.sub_71006F3A70(false);
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

bool NeckSpinBeam::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x3000003)
        _b8.sub_71006F3B14(true);
    else if (message->getType() == 0x3000004)
        _b8.sub_71006F3A70(true);
    return false;
}

}  // namespace uking::action
