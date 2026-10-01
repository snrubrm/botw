#include "Game/AI/AI/aiGuardianMiniTargetOnScalffold.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

GuardianMiniTargetOnScalffold::GuardianMiniTargetOnScalffold(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

GuardianMiniTargetOnScalffold::~GuardianMiniTargetOnScalffold() = default;

void GuardianMiniTargetOnScalffold::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710042902C(true);
}

void GuardianMiniTargetOnScalffold::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GuardianMiniTargetOnScalffold::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mNearDist_s, "NearDist");
}

void GuardianMiniTargetOnScalffold::calc_() {
    sub_71005DB1D8(mActor, *mTargetPos_d);
    getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
    if (getCurrentChild()->isFinished())
        setFinished();
    else if (getCurrentChild()->isFailed())
        setFailed();
    else if (getCurrentChild()->isChangeable())
        sub_710042902C(false);
}

}  // namespace uking::ai
