#include "Game/AI/AI/aiEnemyLifted.h"

namespace uking::ai {

EnemyLifted::EnemyLifted(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool EnemyLifted::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyLifted::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyLifted::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyLifted::m34() {}

void EnemyLifted::loadParams_() {}

bool EnemyLifted::isFinished() const {
    if (ksys::act::ai::Ai::isFinished())
        return true;
    if (isCurrentChild("着地"))
        return getCurrentChild()->isFinished();
    return false;
}

}  // namespace uking::ai
