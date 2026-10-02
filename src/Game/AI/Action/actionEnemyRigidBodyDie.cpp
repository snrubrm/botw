#include "Game/AI/Action/actionEnemyRigidBodyDie.h"

namespace uking::action {

EnemyRigidBodyDie::EnemyRigidBodyDie(const InitArg& arg) : EnemyRigidBodyDieBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
EnemyRigidBodyDie::~EnemyRigidBodyDie() {
    ;
}

bool EnemyRigidBodyDie::init_(sead::Heap* heap) {
    return EnemyRigidBodyDieBase::init_(heap);
}

void EnemyRigidBodyDie::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRigidBodyDieBase::enter_(params);
    if (!mASName_s.isEmpty())
        playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
}

void EnemyRigidBodyDie::leave_() {
    EnemyRigidBodyDieBase::leave_();
}

void EnemyRigidBodyDie::loadParams_() {
    EnemyRigidBodyDieBase::loadParams_();
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRiseSpeed_s, "RiseSpeed");
    getStaticParam(&mASName_s, "ASName");
}

void EnemyRigidBodyDie::calc_() {
    EnemyRigidBodyDieBase::calc_();
    if (isFinishedAS(0, 0))
        setFinished();
}

}  // namespace uking::action
