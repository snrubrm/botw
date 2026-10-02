#include "Game/AI/AI/aiEnemySearchHorse.h"

namespace uking::ai {

// NON_MATCHING: the two param zero stores (0x38/0x48) are emitted in the opposite order
EnemySearchHorse::EnemySearchHorse(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemySearchHorse::~EnemySearchHorse() = default;

bool EnemySearchHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemySearchHorse::enter_(ksys::act::ai::InlineParamPack* params) {
    _100 = ksys::Timer(*mRepathTime_s, *mRepathTime_s);
    if (sub_71003B9914())
        return;
    _58.reset();
    changeChild("馬未発見", params);
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
