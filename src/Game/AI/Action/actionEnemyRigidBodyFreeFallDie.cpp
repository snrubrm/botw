#include "Game/AI/Action/actionEnemyRigidBodyFreeFallDie.h"

namespace uking::action {

EnemyRigidBodyFreeFallDie::EnemyRigidBodyFreeFallDie(const InitArg& arg)
    : EnemyRigidBodyDieBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
EnemyRigidBodyFreeFallDie::~EnemyRigidBodyFreeFallDie() {
    ;
}

bool EnemyRigidBodyFreeFallDie::init_(sead::Heap* heap) {
    return EnemyRigidBodyDieBase::init_(heap);
}

void EnemyRigidBodyFreeFallDie::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRigidBodyDieBase::enter_(params);
    if (!mASName_s.isEmpty())
        playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
}

void EnemyRigidBodyFreeFallDie::leave_() {
    EnemyRigidBodyDieBase::leave_();
}

void EnemyRigidBodyFreeFallDie::loadParams_() {
    EnemyRigidBodyDieBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void EnemyRigidBodyFreeFallDie::calc_() {
    EnemyRigidBodyDieBase::calc_();
    if (isFinishedAS(0, 0))
        setFinished();
}

}  // namespace uking::action
