#include "Game/AI/Action/actionEnemyRigidBodySpinDie.h"

namespace uking::action {

EnemyRigidBodySpinDie::EnemyRigidBodySpinDie(const InitArg& arg) : EnemyRigidBodyDieBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
EnemyRigidBodySpinDie::~EnemyRigidBodySpinDie() {
    ;
}

bool EnemyRigidBodySpinDie::init_(sead::Heap* heap) {
    return EnemyRigidBodyDieBase::init_(heap);
}

void EnemyRigidBodySpinDie::enter_(ksys::act::ai::InlineParamPack* params) {
    _58 = true;
    EnemyRigidBodyDieBase::enter_(params);
    if (!mASName_s.isEmpty())
        playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
}

void EnemyRigidBodySpinDie::leave_() {
    EnemyRigidBodyDieBase::leave_();
}

void EnemyRigidBodySpinDie::loadParams_() {
    EnemyRigidBodyDieBase::loadParams_();
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRiseSpeed_s, "RiseSpeed");
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getStaticParam(&mIsFinishedByBgHit_s, "IsFinishedByBgHit");
    getStaticParam(&mASName_s, "ASName");
}

void EnemyRigidBodySpinDie::calc_() {
    EnemyRigidBodyDieBase::calc_();
}

}  // namespace uking::action
