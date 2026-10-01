#include "Game/AI/AI/aiIsPlacementAreaEnemy.h"

namespace uking::ai {

IsPlacementAreaEnemy::IsPlacementAreaEnemy(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

IsPlacementAreaEnemy::~IsPlacementAreaEnemy() = default;

bool IsPlacementAreaEnemy::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void IsPlacementAreaEnemy::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool IsPlacementAreaEnemy::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool IsPlacementAreaEnemy::isFinished() const {
    return getCurrentChild()->isFinished();
}

void IsPlacementAreaEnemy::leave_() {
    ksys::act::ai::Ai::leave_();
}

void IsPlacementAreaEnemy::loadParams_() {
    getStaticParam(&mCheckType_s, "CheckType");
}

}  // namespace uking::ai
