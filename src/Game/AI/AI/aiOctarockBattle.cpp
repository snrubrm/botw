#include "Game/AI/AI/aiOctarockBattle.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"

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

// NON_MATCHING: the original reads _b4 before the sub_71005D93CC call (same as ShootingEnemyBattle::calc_)
void OctarockBattle::calc_() {
    auto* child = getCurrentChild();
    if (isCurrentChild("吐き出し攻撃") || isCurrentChild("画面外吐き出し攻撃")) {
        if (!_b4 && !m44())
            _b4 = true;

        if (child->isFinished() || child->isFailed()) {
            if (child->isFailed()) {
                setFailed();
            } else {
                sub_7100381ED4();
                m37();
            }
        } else {
            const sead::Vector3f& target = sub_71005D93CC(mActor);
            if (_b4)
                child->setDynamicParam(target, "TargetPos");
            else
                child->setDynamicParam(target + _b8, "TargetPos");
        }
    } else {
        ShootingEnemyBattle::calc_();
    }
    child->setDynamicParam(sub_71005D9548(mActor), "TargetVel");
}

void OctarockBattle::leave_() {
    _118 = _b0;
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

bool OctarockBattle::m44() {
    if (*mIsHideMode_s)
        return true;
    return ShootingEnemyBattle::m44();
}

}  // namespace uking::ai
