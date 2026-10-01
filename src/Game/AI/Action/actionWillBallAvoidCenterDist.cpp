#include "Game/AI/Action/actionWillBallAvoidCenterDist.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

WillBallAvoidCenterDist::WillBallAvoidCenterDist(const InitArg& arg) : WillBallAction(arg) {}

WillBallAvoidCenterDist::~WillBallAvoidCenterDist() = default;

bool WillBallAvoidCenterDist::init_(sead::Heap* heap) {
    return WillBallAction::init_(heap);
}

void WillBallAvoidCenterDist::enter_(ksys::act::ai::InlineParamPack* params) {
    WillBallAction::enter_(params);
}

void WillBallAvoidCenterDist::leave_() {
    WillBallAction::leave_();
}

void WillBallAvoidCenterDist::loadParams_() {
    WillBallAction::loadParams_();
    getStaticParam(&mDist_s, "Dist");
    getStaticParam(&mMaxDist_s, "MaxDist");
    getStaticParam(&mMiddleDist_s, "MiddleDist");
    getDynamicParam(&mCenterPos_d, "CenterPos");
}

// NON_MATCHING: the original loads the actor position before mCenterPos_d (scheduling)
void WillBallAvoidCenterDist::calc_() {
    WillBallAction::calc_();
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    sead::Vector3f diff = *mCenterPos_d - pos;
    diff.y = 0.0f;
    if (diff.length() > *mMaxDist_s)
        setFailed();
}

}  // namespace uking::action
