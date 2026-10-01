#include "Game/AI/AI/aiGuardianMiniRecognizeTarget.h"

namespace uking::ai {

GuardianMiniRecognizeTarget::GuardianMiniRecognizeTarget(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

GuardianMiniRecognizeTarget::~GuardianMiniRecognizeTarget() = default;

void GuardianMiniRecognizeTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool GuardianMiniRecognizeTarget::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void GuardianMiniRecognizeTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GuardianMiniRecognizeTarget::loadParams_() {}

}  // namespace uking::ai
