#include "Game/AI/AI/aiEnemyFindBadStatusFriend.h"

namespace uking::ai {

EnemyFindBadStatusFriend::EnemyFindBadStatusFriend(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyFindBadStatusFriend::~EnemyFindBadStatusFriend() = default;

bool EnemyFindBadStatusFriend::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool EnemyFindBadStatusFriend::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

bool EnemyFindBadStatusFriend::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

bool EnemyFindBadStatusFriend::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyFindBadStatusFriend::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710038BFB0();
}

void EnemyFindBadStatusFriend::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyFindBadStatusFriend::loadParams_() {
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai
