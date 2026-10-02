#include "Game/AI/AI/aiOctarockBattle.h"

namespace uking::ai {

OctarockBattle::OctarockBattle(const InitArg& arg) : ShootingEnemyBattle(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
OctarockBattle::~OctarockBattle() {
    ;
}

bool OctarockBattle::init_(sead::Heap* heap) {
    if (!ShootingEnemyBattle::init_(heap))
        return false;
    _118 = 0;
    return true;
}

void OctarockBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    ShootingEnemyBattle::enter_(params);
}

void OctarockBattle::leave_() {
    ShootingEnemyBattle::leave_();
}

void OctarockBattle::loadParams_() {
    ShootingEnemyBattle::loadParams_();
    getStaticParam(&mActorDisplayRadius_s, "ActorDisplayRadius");
    getStaticParam(&mAttackDistMin_s, "AttackDistMin");
    getStaticParam(&mIsAttackOnlyOutScreen_s, "IsAttackOnlyOutScreen");
    getStaticParam(&mIsHideMode_s, "IsHideMode");
    getStaticParam(&mIsFirstAttackIntervalZero_s, "IsFirstAttackIntervalZero");
    getStaticParam(&mIsLostAttack_s, "IsLostAttack");
    getStaticParam(&mShootActorKey_s, "ShootActorKey");
    getStaticParam(&mVacuumPartsKey_s, "VacuumPartsKey");
}

}  // namespace uking::ai
