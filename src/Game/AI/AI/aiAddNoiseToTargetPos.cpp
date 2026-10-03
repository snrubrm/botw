#include "Game/AI/AI/aiAddNoiseToTargetPos.h"

namespace uking::ai {

addNoiseToTargetPos::addNoiseToTargetPos(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

addNoiseToTargetPos::~addNoiseToTargetPos() = default;

bool addNoiseToTargetPos::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void addNoiseToTargetPos::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void addNoiseToTargetPos::leave_() {
    ksys::act::ai::Ai::leave_();
}

void addNoiseToTargetPos::loadParams_() {
    getStaticParam(&mRandYMin_s, "RandYMin");
    getStaticParam(&mRandYMax_s, "RandYMax");
    getStaticParam(&mRandLeftMax_s, "RandLeftMax");
    getStaticParam(&mRandRightMax_s, "RandRightMax");
    getStaticParam(&mRandDistMin_s, "RandDistMin");
    getStaticParam(&mRandDistMax_s, "RandDistMax");
    getStaticParam(&mIsUpdateEveryFrame_s, "IsUpdateEveryFrame");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
