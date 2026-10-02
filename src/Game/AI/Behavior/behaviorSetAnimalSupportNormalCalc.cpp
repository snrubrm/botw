#include "Game/AI/Behavior/behaviorSetAnimalSupportNormalCalc.h"

namespace uking::behavior {

SetAnimalSupportNormalCalc::SetAnimalSupportNormalCalc(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

SetAnimalSupportNormalCalc::~SetAnimalSupportNormalCalc() = default;

bool SetAnimalSupportNormalCalc::m6(sead::Heap* heap) {
    return true;
}

void SetAnimalSupportNormalCalc::m7() {}

void SetAnimalSupportNormalCalc::loadParams() {
    getStaticParam(&mRayCastLength_s, "RayCastLength");
    getStaticParam(&mPriorRayCastLength_s, "PriorRayCastLength");
    getStaticParam(&mPosteriorLimbOffset_s, "PosteriorLimbOffset");
    getStaticParam(&mPriorLimbOffset_s, "PriorLimbOffset");
}

}  // namespace uking::behavior
