#include "Game/AI/AI/aiEnemyTargetGearSelect.h"

namespace uking::ai {

EnemyTargetGearSelect::EnemyTargetGearSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyTargetGearSelect::~EnemyTargetGearSelect() = default;

bool EnemyTargetGearSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyTargetGearSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool EnemyTargetGearSelect::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool EnemyTargetGearSelect::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

void EnemyTargetGearSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyTargetGearSelect::loadParams_() {
    getStaticParam(&mGearThreashold_s, "GearThreashold");
    getStaticParam(&mIsSelectEveryFrame_s, "IsSelectEveryFrame");
}

}  // namespace uking::ai
