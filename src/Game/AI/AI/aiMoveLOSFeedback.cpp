#include "Game/AI/AI/aiMoveLOSFeedback.h"

namespace uking::ai {

MoveLOSFeedback::MoveLOSFeedback(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MoveLOSFeedback::~MoveLOSFeedback() = default;

bool MoveLOSFeedback::init_(sead::Heap* heap) {
    _50 = ksys::Timer(0, 0);
    return true;
}

void MoveLOSFeedback::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void MoveLOSFeedback::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MoveLOSFeedback::loadParams_() {
    getStaticParam(&mFramesCooldownFeedback_s, "FramesCooldownFeedback");
    getStaticParam(&mLOSCheckLength_s, "LOSCheckLength");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
