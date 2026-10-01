#include "Game/AI/AI/aiPriestBossEyeBeamThird.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

PriestBossEyeBeamThird::PriestBossEyeBeamThird(const InitArg& arg) : PriestBossEyeBeam(arg) {}

PriestBossEyeBeamThird::~PriestBossEyeBeamThird() = default;

bool PriestBossEyeBeamThird::init_(sead::Heap* heap) {
    return PriestBossEyeBeam::init_(heap);
}

void PriestBossEyeBeamThird::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossEyeBeam::enter_(params);
}

void PriestBossEyeBeamThird::calc_() {
    PriestBossEyeBeam::calc_();
    if (isCurrentChild("照準") || isCurrentChild("チャージ"))
        sub_7100516FAC(*mDestinationPos_a, *mIsArrivedAtDestination_a);
    else if (isCurrentChild("発射"))
        *mDestinationPos_a = mActor->getMtx().getTranslation();
}

void PriestBossEyeBeamThird::leave_() {
    PriestBossEyeBeam::leave_();
}

void PriestBossEyeBeamThird::loadParams_() {
    PriestBossEyeBeam::loadParams_();
    getAITreeVariable(&mIsArrivedAtDestination_a, "IsArrivedAtDestination");
    getAITreeVariable(&mDestinationPos_a, "DestinationPos");
    getAITreeVariable(&mFacePos_a, "FacePos");
}

}  // namespace uking::ai
