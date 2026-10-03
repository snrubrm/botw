#include "Game/AI/AI/aiGiantEarthReleaseAttack.h"

namespace uking::ai {

GiantEarthReleaseAttack::GiantEarthReleaseAttack(const InitArg& arg) : EarthReleaseAttack(arg) {}

GiantEarthReleaseAttack::~GiantEarthReleaseAttack() = default;

bool GiantEarthReleaseAttack::init_(sead::Heap* heap) {
    return EarthReleaseAttack::init_(heap);
}

void GiantEarthReleaseAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    *mIsArrivedAtDestination_a = false;
    *mKeepDistFromGround_a = *mStartHeight_s;
    changeChild("準備");
}

void GiantEarthReleaseAttack::leave_() {
    EarthReleaseAttack::leave_();
    *mKeepDistFromGround_a = -1.0f;
}

void GiantEarthReleaseAttack::loadParams_() {
    EarthReleaseAttack::loadParams_();
    getStaticParam(&mStartHeight_s, "StartHeight");
    getStaticParam(&mStartDistFromTarget_s, "StartDistFromTarget");
    getAITreeVariable(&mKeepDistFromGround_a, "KeepDistFromGround");
    getAITreeVariable(&mIsArrivedAtDestination_a, "IsArrivedAtDestination");
    getAITreeVariable(&mDestinationPos_a, "DestinationPos");
}

void GiantEarthReleaseAttack::calc_() {
    if (isCurrentChild("準備")) {
        if (*mIsArrivedAtDestination_a)
            changeToPreAction();
    } else {
        EarthReleaseAttack::calc_();
    }
}

}  // namespace uking::ai
