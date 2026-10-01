#include "Game/AI/AI/aiEnemyLost.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

EnemyLost::EnemyLost(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyLost::~EnemyLost() = default;

bool EnemyLost::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyLost::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000000);
    m34();
}

bool EnemyLost::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool EnemyLost::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

bool EnemyLost::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void EnemyLost::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyLost::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mRailCheckInterval_s, "RailCheckInterval");
    getStaticParam(&mSealForceReturn_s, "SealForceReturn");
    getStaticParam(&mForceReturnNoCameraRad_s, "ForceReturnNoCameraRad");
}

}  // namespace uking::ai
