#include "Game/AI/AI/aiEnemyRoamSelect.h"

namespace uking::ai {

EnemyRoamSelect::EnemyRoamSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyRoamSelect::~EnemyRoamSelect() = default;

bool EnemyRoamSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyRoamSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool EnemyRoamSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool EnemyRoamSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool EnemyRoamSelect::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void EnemyRoamSelect::leave_() {
    _78 = false;
}

void EnemyRoamSelect::loadParams_() {
    getStaticParam(&mHideGrassHeight_s, "HideGrassHeight");
    getDynamicParam(&mCentralPos_d, "CentralPos");
    getStaticParam(&mNotReturnDist_s, "NotReturnDist");
}

}  // namespace uking::ai
