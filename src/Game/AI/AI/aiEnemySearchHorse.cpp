#include "Game/AI/AI/aiEnemySearchHorse.h"

namespace uking::ai {

EnemySearchHorse::EnemySearchHorse(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemySearchHorse::~EnemySearchHorse() = default;

bool EnemySearchHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemySearchHorse::enter_(ksys::act::ai::InlineParamPack* params) {
    _100 = ksys::Timer(*mParams.mRepathTime_s, *mParams.mRepathTime_s);
    if (sub_71003B9914())
        return;
    _58.reset();
    changeChild("馬未発見", params);
}

void EnemySearchHorse::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemySearchHorse::loadParams_() {
    getStaticParam(&mParams.mRepathTime_s, "RepathTime");
    getStaticParam(&mParams.mSearchDist_s, "SearchDist");
    getStaticParam(&mParams.mRideRadius_s, "RideRadius");
    getStaticParam(&mParams.mNoWeaponRiding_s, "NoWeaponRiding");
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
