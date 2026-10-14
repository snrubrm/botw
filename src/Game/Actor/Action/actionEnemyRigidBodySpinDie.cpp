#include "Game/Actor/Action/actionEnemyRigidBodySpinDie.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiUnk_710072BA90.h"
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

// NON_MATCHING: the original computes the linear velocity before the spin axis and the scaled axis before
// storing the velocity (scheduling only; see lane3 log, borderline locals).
// Like EnemyRigidBodyDie::m32, plus a spin around the horizontal axis perpendicular to the blow direction.
void EnemyRigidBodySpinDie::m32(sead::Vector3f* velocity, sead::Vector3f* angular_velocity) {
    auto* actor = mActor;
    if (!actor->getDamageMgr()) {
        EnemyRigidBodyDieBase::m32(velocity, angular_velocity);
        return;
    }

    sead::Vector3f up = getGravity(actor) * (1.0f / 900.0f);
    up.normalize();

    sead::Vector3f dir{0.0f, 0.0f, 1.0f};
    auto* damage_mgr = sub_710072BA90(mActor);
    sub_71005E2318(&dir, mActor, damage_mgr);
    sead::Vector3f axis;
    axis.setCross(sead::Vector3f::ey, dir);
    if (axis.x == 0.0f && axis.y == 0.0f && axis.z == 0.0f)
        axis.setRotated(actor->getMtx(), sead::Vector3f(-1.0f, 0.0f, 0.0f));
    axis.normalize();
    *velocity = (dir * *mSpeed_s - up * *mRiseSpeed_s) * 30.0f;
    *angular_velocity = axis * *mRotSpeed_s * 30.0f;
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
