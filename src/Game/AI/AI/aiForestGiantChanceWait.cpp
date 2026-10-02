#include "Game/AI/AI/aiForestGiantChanceWait.h"
#include "Game/Actor/actEnemy.h"

namespace uking::ai {

ForestGiantChanceWait::ForestGiantChanceWait(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ForestGiantChanceWait::~ForestGiantChanceWait() = default;

bool ForestGiantChanceWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ForestGiantChanceWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ForestGiantChanceWait::leave_() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e68.rate = -1.0f;
}

void ForestGiantChanceWait::loadParams_() {
    getStaticParam(&mChanceRate_s, "ChanceRate");
    getStaticParam(&mCorrectRate_s, "CorrectRate");
    getStaticParam(&mTurnStartAngle_s, "TurnStartAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool ForestGiantChanceWait::isChangeable() const {
    if (ksys::act::ai::Ai::isChangeable())
        return true;
    auto* child = getCurrentChild();
    if (child->isFinished())
        return true;
    return child->isFailed();
}

}  // namespace uking::ai
