#include "Game/AI/AI/aiEternalPlayerTarget.h"

namespace uking::ai {

EternalPlayerTarget::EternalPlayerTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EternalPlayerTarget::~EternalPlayerTarget() = default;

bool EternalPlayerTarget::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool EternalPlayerTarget::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool EternalPlayerTarget::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

bool EternalPlayerTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EternalPlayerTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71003C9AAC(true);
}

void EternalPlayerTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EternalPlayerTarget::loadParams_() {}

}  // namespace uking::ai
