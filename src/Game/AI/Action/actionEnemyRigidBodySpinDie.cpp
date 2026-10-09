#include "Game/AI/Action/actionEnemyRigidBodySpinDie.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

// Native calc_ constructs an eight-byte IDelegate2R filter with this three-slot table.
class Unk_710237a2d8 : public sead::IDelegate2R<ksys::phys::RigidBody*, ksys::phys::RigidBody*, bool> {
public:
    bool invoke(ksys::phys::RigidBody*, ksys::phys::RigidBody* other) override;
};
KSYS_CHECK_SIZE_NX150(Unk_710237a2d8, 8);

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
    if (_58) {
        _58 = false;
        return;
    }
    if (!*mIsFinishedByBgHit_s)
        return;
    if (auto* body = mActor->getMainBody()) {
        Unk_710237a2d8 filter;
        if (ksys::act::sub_7100EEB078(body, nullptr, &filter))
            setFinished();
    }
}

bool Unk_710237a2d8::invoke(ksys::phys::RigidBody*, ksys::phys::RigidBody* other) {
    switch (other->getContactLayer().value()) {
    case ksys::phys::ContactLayer::EntityObject:
    case ksys::phys::ContactLayer::EntityGroundObject:
    case ksys::phys::ContactLayer::EntityGround:
    case ksys::phys::ContactLayer::EntityGroundSmooth:
    case ksys::phys::ContactLayer::EntityGroundRough:
        return true;
    default:
        return false;
    }
}

}  // namespace uking::action
