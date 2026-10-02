#include "Game/AI/AI/aiEnemySearchHorse.h"

namespace uking::ai {

EnemySearchHorse::EnemySearchHorse(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemySearchHorse::~EnemySearchHorse() = default;

bool EnemySearchHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemySearchHorse::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemySearchHorse::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemySearchHorse::loadParams_() {
    getStaticParam(&mRepathTime_s, "RepathTime");
    getStaticParam(&mSearchDist_s, "SearchDist");
    getStaticParam(&mRideRadius_s, "RideRadius");
    getStaticParam(&mNoWeaponRiding_s, "NoWeaponRiding");
}

bool EnemySearchHorse::isFailed() const {
    if (ActionBase::isFailed())
        return true;
    if (isCurrentChild("馬未発見"))
        return getCurrentChild()->isFailed();
    return false;
}

bool EnemySearchHorse::isFinished() const {
    if (ActionBase::isFinished())
        return true;
    if (isCurrentChild("馬未発見"))
        return getCurrentChild()->isFinished();
    return false;
}

}  // namespace uking::ai
