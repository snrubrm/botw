#include "Game/AI/AI/aiBokoblinHoldArrow.h"

namespace uking::ai {

BokoblinHoldArrow::BokoblinHoldArrow(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void BokoblinHoldArrow::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool BokoblinHoldArrow::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void BokoblinHoldArrow::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
