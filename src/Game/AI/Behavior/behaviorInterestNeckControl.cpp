#include "Game/AI/Behavior/behaviorInterestNeckControl.h"

namespace uking::behavior {

InterestNeckControl::InterestNeckControl(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

InterestNeckControl::~InterestNeckControl() = default;

void InterestNeckControl::loadParams() {
    getStaticParam(&mIgnorePlayerByTimePass_s, "IgnorePlayerByTimePass");
}

}  // namespace uking::behavior
