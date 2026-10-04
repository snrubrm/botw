#include "Game/AI/Action/actionForkGanonBeastBeamShoot.h"

namespace uking::action {

ForkGanonBeastBeamShoot::ForkGanonBeastBeamShoot(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkGanonBeastBeamShoot::~ForkGanonBeastBeamShoot() = default;

bool ForkGanonBeastBeamShoot::init_(sead::Heap* heap) {
    sead::Vector3f dir = *mBeamDir_s;
    dir.normalize();
    _68.sub_71006F331C(heap, mBeamActorName_s, mBeamActorKey_s, mBeamBoneName_s, *mBeamRange_s,
                       250.0f, mMuzzleOffset_s, &dir, -1);
    return true;
}

void ForkGanonBeastBeamShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    _128 = false;
    _68.sub_71006F3BC4(mBeamDir_s);
    _68._10 = *mMuzzleOffset_s;
}

void ForkGanonBeastBeamShoot::leave_() {
    if (_128) {
        _128 = false;
        _68.sub_71006F3B14(false);
    }
}

void ForkGanonBeastBeamShoot::loadParams_() {
    getStaticParam(&mBeamRange_s, "BeamRange");
    getStaticParam(&mBeamBoneName_s, "BeamBoneName");
    getStaticParam(&mBeamActorKey_s, "BeamActorKey");
    getStaticParam(&mBeamActorName_s, "BeamActorName");
    getStaticParam(&mMuzzleOffset_s, "MuzzleOffset");
    getStaticParam(&mBeamDir_s, "BeamDir");
}

void ForkGanonBeastBeamShoot::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
