#include "Game/AI/Action/actionForkAerialAcrobatics.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

// NON_MATCHING: instruction scheduling (stp of the 0x40 params vs add x0)
ForkAerialAcrobatics::ForkAerialAcrobatics(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkAerialAcrobatics::~ForkAerialAcrobatics() = default;

bool ForkAerialAcrobatics::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkAerialAcrobatics::enter_(ksys::act::ai::InlineParamPack* params) {
    _60 = false;
    if (auto* cc = mActor->getCharacterController())
        _5c = cc->get110();
    mFlags.set(Flag::Changeable);
}

void ForkAerialAcrobatics::leave_() {
    if (auto* cc = mActor->getCharacterController())
        cc->sub_7100F5EEB8(_5c);
}

void ForkAerialAcrobatics::loadParams_() {
    getStaticParam(&mSpeedKeepRatio_s, "SpeedKeepRatio");
    getStaticParam(&mRotSpeedKeepRatio_s, "RotSpeedKeepRatio");
    getStaticParam(&mMinGravityScale_s, "MinGravityScale");
    getStaticParam(&mGravityPer_s, "GravityPer");
    getStaticParam(&mRetGravityPer_s, "RetGravityPer");
    getStaticParam(&mIsStopGravitySpeed_s, "IsStopGravitySpeed");
}

void ForkAerialAcrobatics::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
