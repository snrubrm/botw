#include "Game/AI/AI/aiEnemyNoticeLimit.h"

namespace uking::ai {

EnemyNoticeLimit::EnemyNoticeLimit(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool EnemyNoticeLimit::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyNoticeLimit::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool EnemyNoticeLimit::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool EnemyNoticeLimit::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

void EnemyNoticeLimit::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyNoticeLimit::loadParams_() {
    getStaticParam(&mOverNum_s, "OverNum");
}

bool EnemyNoticeLimit::isChangeable() const {
    if (ksys::act::ai::Ai::isChangeable())
        return true;
    return getCurrentChild()->isChangeable();
}

}  // namespace uking::ai
