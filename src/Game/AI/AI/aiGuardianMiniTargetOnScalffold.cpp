#include "Game/AI/AI/aiGuardianMiniTargetOnScalffold.h"

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

}  // namespace uking::ai
