#include "Game/AI/Action/actionEnemyRigidBodyDie.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "KingSystem/ActorSystem/actActor.h"

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

// NON_MATCHING: scheduling (the original loads mActor again after sub_710072BA90 and computes the first vector with
// the loads / stores in a different order)
void EnemyRigidBodyDie::m32(sead::Vector3f* velocity, sead::Vector3f* angular_velocity) {
    auto* actor = mActor;
    if (!actor->getDamageMgr()) {
        EnemyRigidBodyDieBase::m32(velocity, angular_velocity);
        return;
    }

    sead::Vector3f gravity;
    sub_710072DC50(&gravity, actor);
    sead::Vector3f up = gravity * (1.0f / 900.0f);
    up.normalize();

    sead::Vector3f dir{0.0f, 0.0f, 1.0f};
    sub_71005E2318(&dir, mActor, sub_710072BA90(mActor));
    *velocity = (dir * *mSpeed_s - up * *mRiseSpeed_s) * 30.0f;
    *angular_velocity = actor->getAngVelocity() * 30.0f;
}

}  // namespace uking::action
