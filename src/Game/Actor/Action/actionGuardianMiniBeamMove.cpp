#include "Game/Actor/Action/actionGuardianMiniBeamMove.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"
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

// NON_MATCHING: hit-position and contact-iterator stack slots differ.
void GuardianMiniBeamMove::leave_() {
    sead::Vector3f hit_position;
    bool has_position = false;
    if (hasAttackInfo(mActor)) {
        if (auto* info = getAttackInfo(mActor, 0)) {
            hit_position = info->_0;
            has_position = true;
        }
    }
    if (!has_position) {
        if (auto* body = mActor->getMainBody()) {
            auto* contacts = body->getContactPointInfo();
            if (contacts && contacts->getNumContactPoints() != 0 && !contacts->begin().isEnd()) {
                contacts = body->getContactPointInfo();
                if (contacts && contacts->getNumContactPoints() != 0 && !contacts->begin().isEnd()) {
                    auto it = contacts->begin();
                    if (it != contacts->end()) {
                        it.getPointPosition(&hit_position, ksys::phys::ContactPointInfo::Iterator::Point::BodyA);
                        has_position = true;
                    }
                }
            }
        }
    }
    if (has_position) {
        sead::Matrix34f transform;
        if (auto* body = mActor->getMainBody()) {
            body->getTransform(&transform);
            transform.setTranslation(hit_position);
            body->changePositionAndRotation(transform, sead::Mathf::epsilon());
        }
        if (auto* body = mActor->findPhysicsBodyByName("Atk", "AtkBody"))
            body->changePositionAndRotation(transform, sead::Mathf::epsilon());
    }
    sub_71001943F0();
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

// NON_MATCHING: contact-iterator stack slots and range-query loads are reordered.
bool GuardianMiniBeamMove::isFinished() const {
    auto* actor = mActor;
    if (!actor)
        return false;
    if (hasAttackInfo(actor)) {
        auto* info = getAttackInfo(actor, 0);
        if (info && (info->_18 & 0xa))
            return BeamMove::isFinished();
        return true;
    }
    auto* body = actor->getMainBody();
    auto* contacts = body ? body->getContactPointInfo() : nullptr;
    if (!contacts || contacts->getNumContactPoints() == 0 || contacts->begin().isEnd()) {
        const auto position = actor->getMtx().getTranslation();
        sead::Vector3f home;
        actor->getHomePos(&home);
        home -= position;
        const f32 range = actor->getParam()->getRes().mGParamList->getAttack()->mRange.ref();
        return home.squaredLength() >= range * range;
    }
    contacts = body->getContactPointInfo();
    if (contacts && contacts->getNumContactPoints() != 0 && !contacts->begin().isEnd()) {
        auto it = contacts->begin();
        if (it != contacts->end()) {
            // The native queries this point even though the position is not used afterwards.
            sead::Vector3f contact_position;
            it.getPointPosition(&contact_position, ksys::phys::ContactPointInfo::Iterator::Point::BodyA);
        }
    }
    body = mActor->findPhysicsBodyByName("Atk", "AtkBody");
    contacts = body ? body->getContactPointInfo() : nullptr;
    return !contacts || contacts->getNumContactPoints() == 0 || contacts->begin().isEnd();
}

}  // namespace uking::action
