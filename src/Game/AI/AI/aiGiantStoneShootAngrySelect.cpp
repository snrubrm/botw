#include "Game/AI/AI/aiGiantStoneShootAngrySelect.h"

namespace uking::ai {

GiantStoneShootAngrySelect::GiantStoneShootAngrySelect(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

GiantStoneShootAngrySelect::~GiantStoneShootAngrySelect() = default;

bool GiantStoneShootAngrySelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool GiantStoneShootAngrySelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool GiantStoneShootAngrySelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GiantStoneShootAngrySelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GiantStoneShootAngrySelect::calc_() {}

void GiantStoneShootAngrySelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GiantStoneShootAngrySelect::loadParams_() {
    getStaticParam(&mThrowableAngryRate_s, "ThrowableAngryRate");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mIgniteHandle_d, "IgniteHandle");
}

}  // namespace uking::ai
