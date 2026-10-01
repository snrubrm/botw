#include "Game/AI/AI/aiEnemyLifeSelect.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

EnemyLifeSelect::EnemyLifeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyLifeSelect::~EnemyLifeSelect() = default;

bool EnemyLifeSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool EnemyLifeSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool EnemyLifeSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyLifeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!mActor->getMapObject())
        changeChild("ハンター", params);
    else if (*mIsWatchKeeping_m)
        changeChild("見張り", params);
    else
        changeChild("一般", params);
}

void EnemyLifeSelect::calc_() {}

void EnemyLifeSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyLifeSelect::loadParams_() {
    getMapUnitParam(&mIsWatchKeeping_m, "IsWatchKeeping");
}

}  // namespace uking::ai
