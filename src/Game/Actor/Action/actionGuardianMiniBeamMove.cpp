#include "Game/Actor/Action/actionGuardianMiniBeamMove.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

// `_78()`: value-initialisation zero-fills the whole 0x20-byte handle pair incl. padding (as WeaponRootAI's `_c8()`)
GuardianMiniBeamMove::GuardianMiniBeamMove(const InitArg& arg) : BeamMove(arg), _78() {}

GuardianMiniBeamMove::~GuardianMiniBeamMove() = default;

void GuardianMiniBeamMove::enter_(ksys::act::ai::InlineParamPack* params) {
    BeamMove::enter_(params);
    _98 = 0;
    if (auto* body = mActor->getMainBody())
        body->setGravityFactor(0.0f);
    xlinkSearchAndEmit(mActor, "Beam", 2, &_78);
}

void GuardianMiniBeamMove::leave_() {
    BeamMove::leave_();
}

void GuardianMiniBeamMove::loadParams_() {
    BeamMove::loadParams_();
    getStaticParam(&mReboundDeccel_s, "ReboundDeccel");
}

void GuardianMiniBeamMove::calc_() {
    if (BeamMove::m38())
        return;
    if (hasAttackInfo(mActor)) {
        auto* info = getAttackInfo(mActor, 0);
        if (info->_18 & 0xa) {
            m33(info);
            sub_71001943F0();
            xlinkSearchAndEmit(mActor, "Beam", 2, &_78);
        } else {
            m36(info);
        }
        return;
    }
    if (sub_7100193EB4())
        return;
    sub_71000C1258();
    sub_71001940D0();
    if (_98 == 0) {
        if (auto* body = mActor->getMainBody())
            body->setLinearVelocity(sead::Vector3f::zero);
        if (auto* body = mActor->findPhysicsBodyByName("Atk", "AtkBody"))
            body->setLinearVelocity(sead::Vector3f::zero);
        _98 = 1;
    }
}


// NON_MATCHING: vector stack allocation and scalar multiplication scheduling.
void GuardianMiniBeamMove::sub_71001940D0() {
    auto* body = mActor->getMainBody();
    if (!body)
        return;
    sead::Matrix34f transform;
    body->getTransform(&transform);
    sead::Vector3f forward = transform.getBase(2);
    sead::Vector3f velocity;
    body->getLinearVelocity(&velocity);
    forward.normalize();
    velocity.normalize();
    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, forward, velocity, sead::Vector3f::ey);
    body->setAngularVelocity(axis * angle * 30.0f);
}

void GuardianMiniBeamMove::sub_71001943F0() {
    _78.mELink.kill();
    _78.mSLink.fade();
}

}  // namespace uking::action
