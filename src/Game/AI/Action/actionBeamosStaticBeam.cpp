#include "Game/AI/Action/actionBeamosStaticBeam.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::action {

BeamosStaticBeam::BeamosStaticBeam(const InitArg& arg) : StopASPlay(arg) {}

BeamosStaticBeam::~BeamosStaticBeam() = default;

bool BeamosStaticBeam::init_(sead::Heap* heap) {
    return StopASPlay::init_(heap);
}

void BeamosStaticBeam::enter_(ksys::act::ai::InlineParamPack* params) {
    StopASPlay::enter_(params);
    mFlags.set(Flag::Changeable);
    _a8.sub_71006F3B84();
    _a8.sub_71006F3A70(false);
}

void BeamosStaticBeam::leave_() {
    _a8.sub_71006F3B14(false);
    StopASPlay::leave_();
}

void BeamosStaticBeam::loadParams_() {
    StopASPlay::loadParams_();
    getStaticParam(&mBeamRange_s, "BeamRange");
    getStaticParam(&mBeamSpeed_s, "BeamSpeed");
    getStaticParam(&mUseDynamicCutting_s, "UseDynamicCutting");
    getStaticParam(&mBeamBoneName_s, "BeamBoneName");
    getStaticParam(&mBeamActorName_s, "BeamActorName");
    getStaticParam(&mBeamActorKey_s, "BeamActorKey");
    getStaticParam(&mMuzzleOffset_s, "MuzzleOffset");
    getStaticParam(&mBeamDirection_s, "BeamDirection");
    getMapUnitParam(&mBeamRange_m, "BeamRange");
}

void BeamosStaticBeam::calc_() {
    StopASPlay::calc_();
    if (mActor->getXLink()->_cc.isOnBit(14))
        _a8.sub_71006F38A4(mActor);
    _a8.sub_71006F3A6C();
}

}  // namespace uking::action
