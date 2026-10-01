#include "Game/AI/AI/aiInForceEnemyLostAreaSelect.h"

namespace uking::ai {

InForceEnemyLostAreaSelect::InForceEnemyLostAreaSelect(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

InForceEnemyLostAreaSelect::~InForceEnemyLostAreaSelect() = default;

bool InForceEnemyLostAreaSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool InForceEnemyLostAreaSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool InForceEnemyLostAreaSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void InForceEnemyLostAreaSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void InForceEnemyLostAreaSelect::calc_() {}

void InForceEnemyLostAreaSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void InForceEnemyLostAreaSelect::loadParams_() {}

}  // namespace uking::ai
