#include "Game/AI/AI/aiEnemyCutRope.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

EnemyCutRope::EnemyCutRope(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyCutRope::~EnemyCutRope() = default;

bool EnemyCutRope::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyCutRope::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyCutRope::leave_() {
    ksys::act::ActorConstDataAccess acc;
    ksys::act::acquireActor(mTargetActor_d, &acc);
}

void EnemyCutRope::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mCutDist_s, "CutDist");
    getStaticParam(&mCutAngle_s, "CutAngle");
    getStaticParam(&mCutFlyAttack_s, "CutFlyAttack");
    getDynamicParam(&mTargetActor_d, "TargetActor");
    getDynamicParam(&mCommanderID_d, "CommanderID");
}

}  // namespace uking::ai
