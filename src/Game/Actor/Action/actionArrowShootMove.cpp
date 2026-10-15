#include "Game/Actor/Action/actionArrowShootMove.h"
#include <math/seadQuat.h>
#include "Game/Actor/Damage/dmgInfoManager.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

ArrowShootMove::ArrowShootMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

void ArrowShootMove::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    auto* bullet = sead::DynamicCast<ksys::act::Bullet>(mActor);
    _148 = bullet ? (bullet->_cf4 >> 1) & 1 : 0;
    sub_71000A2A64();
    _140 = -1;
    _14a = *mIsShootByPlayer_d;
}

void ArrowShootMove::leave_() {
    if (!_149)
        sub_71000A331C();

    if (_138) {
        _138->setLinearVelocity(sead::Vector3f::zero, sead::Mathf::epsilon());
        _138->setAngularVelocity(sead::Vector3f::zero, sead::Mathf::epsilon());
        sub_71007A2D34(_138);
    }
}

void ArrowShootMove::loadParams_() {
    getDynamicParam(&mIsShootByPlayer_d, "IsShootByPlayer");
    getDynamicParam(&mFirstSpeed_d, "FirstSpeed");
    getDynamicParam(&mAccel_d, "Accel");
    getDynamicParam(&mAimSpeed_d, "AimSpeed");
    getDynamicParam(&mFallAccel_d, "FallAccel");
    getDynamicParam(&mFallAimSpeed_d, "FallAimSpeed");
    getDynamicParam(&mGravity_d, "Gravity");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mAtPoint_d, "AtPoint");
    getDynamicParam(&mAtRange_d, "AtRange");
    getDynamicParam(&mAtImpulse_d, "AtImpulse");
    getDynamicParam(&mAtImpact_d, "AtImpact");
    getDynamicParam(&mRelativeVel_d, "RelativeVel");
    getDynamicParam(&mAtAttr_d, "AtAttr");
    getStaticParam(&mFallSpeedRatioByRange_s, "FallSpeedRatioByRange");
    getDynamicParam(&mAtMinDamage_d, "AtMinDamage");
}

// NON_MATCHING: matrix and collision-result stack slots differ.
void ArrowShootMove::calc_() {
    m33();
    m38();
    sub_71000A2EE0();
    sead::Vector3f actor_position;
    mActor->getMtx().getTranslation(actor_position);
    if (!ksys::map::PlacementMgr::instance()->isStaticCompoundReady(actor_position, false))
        return;
    bool a = false;
    bool b = false;
    sead::Vector3f velocity = sead::Vector3f::zero;
    sead::Vector3f position;
    if (!m34(&position, &a, &b, &velocity))
        return;
    _128 = position;
    if (b) {
        auto* body = mActor->getMainBody();
        if (body && _138) {
            sead::Matrix34f mtx = mActor->getMtx();
            mtx.setTranslation(position);
            body->changePositionAndRotation(mtx, sead::Mathf::epsilon());
            _138->changePositionAndRotation(mtx, sead::Mathf::epsilon());
        }
        return;
    }
    const sead::Vector3f forward = mActor->getMtx().getBase(2);
    _128 -= forward * m32();
    if (a || _148)
        _128 -= forward * m32();
    auto* body = mActor->getMainBody();
    if (body && _138) {
        sead::Matrix34f mtx = mActor->getMtx();
        _128 += velocity;
        mtx.setTranslation(_128);
        body->changePositionAndRotation(mtx, sead::Mathf::epsilon());
        _138->changePositionAndRotation(mtx, sead::Mathf::epsilon());
    }
    m42();
    if (velocity.x == 0.0f && velocity.y == 0.0f && velocity.z == 0.0f)
        setFinished();
}

float ArrowShootMove::m32() {
    return 0.5f;
}

// NON_MATCHING: fall-speed clamping and switch block layout differ.
void ArrowShootMove::m33() {
    switch (_140) {
    case -1:
        m37();
        _140 = 0;
        break;
    case 1:
        sub_71000A369C();
        break;
    case 0:
        m37();
        if (!m40())
            break;
        _100 = *mFallAimSpeed_d;
        _100 += (*mAtRange_d / 20.0f - 1.0f) * *mFallSpeedRatioByRange_s;
        if (_100 < 0.0f)
            _100 = 0.0f;
        else if (_100 > *mAimSpeed_d)
            _100 = *mAimSpeed_d;
        _fc = sead::Mathf::abs(*mFallAccel_d);
        _104.set(0.0f, *mGravity_d, 0.0f);
        if (sead::Mathf::equalsEpsilon(0.0f, _fc))
            _100 = _b4.value;
        if (sead::Mathf::equalsEpsilon(0.0f, _100))
            _100 = sead::Mathf::abs(_104.y);
        _144 = 0;
        _140 = 1;
        break;
    }
}

bool ArrowShootMove::m35(const ksys::act::ActorLinkConstDataAccess& accessor) {
    return false;
}

void ArrowShootMove::m36(bool* out, const ksys::act::ActorLinkConstDataAccess& accessor) {}

void ArrowShootMove::m39(sead::Vector3f* out) {
    *out = _e4;
}

bool ArrowShootMove::m40() {
    if (*mAtRange_d <= 10.0f)
        return true;
    sead::Vector3f diff = _11c;
    diff -= mActor->getMtx().getTranslation();
    return diff.length() >= *mAtRange_d;
}

f32 ArrowShootMove::m41() {
    return 0.0f;
}

void ArrowShootMove::m42() {}

// NON_MATCHING: the velocity stays in integer registers around the damage-state query.
void ArrowShootMove::sub_71000A369C() {
    auto* body = mActor->getMainBody();
    if (!body)
        return;
    _b4 += _fc;
    if (_fc < 0.0f)
        _b4.setToMax(_100);
    else if (_fc > 0.0f)
        _b4.setToMin(_100);
    _b4.updateStats();
    sead::Vector3f velocity;
    velocity = _110;
    if (act::DamageInfoMgr::sub_7100674764()) {
        const sead::Vector3f relative_velocity = *mRelativeVel_d;
        velocity -= relative_velocity;
    }
    velocity.normalize();
    velocity = velocity * _b4.value + _104;
    if (act::DamageInfoMgr::sub_7100674764()) {
        const sead::Vector3f relative_velocity = *mRelativeVel_d;
        velocity += relative_velocity;
    }
    _110 = velocity;
    body->setLinearVelocity(velocity * 30.0f, sead::Mathf::epsilon());
}

// NON_MATCHING: matrix values and quaternion temporaries are scheduled differently.
void ArrowShootMove::sub_71000A2EE0() {
    if (!_138)
        return;
    auto* body = mActor->getMainBody();
    if (!body)
        return;
    sead::Vector3f velocity;
    body->getLinearVelocity(&velocity);
    velocity = velocity * (1.0f / 30.0f);
    velocity *= ksys::VFR::instance()->getDeltaFrame();
    sead::Vector3f angular_velocity;
    body->getAngularVelocity(&angular_velocity);
    angular_velocity = angular_velocity * (1.0f / 30.0f);
    angular_velocity *= ksys::VFR::instance()->getDeltaFrame();
    sead::Matrix34f current;
    body->getTransform(&current);
    const sead::Vector3f position = current.getTranslation() + velocity;
    const f32 angle = angular_velocity.normalize();
    sead::Quatf quaternion;
    quaternion.setAxisRadian(angular_velocity, angle);
    sead::Matrix33f rotation;
    rotation.fromQuat(quaternion);
    sead::Matrix34f result;
    sead::Matrix34CalcCommon<f32>::multiply(result, current, rotation);
    result.setTranslation(position);
    _138->changePositionAndRotation(result, sead::Mathf::epsilon());
}

// NON_MATCHING: initial value stores and speed selection are scheduled differently.
void ArrowShootMove::sub_71000A2A64() {
    const f32 speed = mFirstSpeed_d->length();
    _b4.value = speed;
    _b4.prev_value = speed;
    _c0.value = sead::Vector3f::zero;
    _c0.prev_value = _c0.value;
    _fc = *mAccel_d;
    const f32 aim_speed = *mAimSpeed_d;
    _100 = sead::Mathf::equalsEpsilon(0.0f, _fc) ? speed : aim_speed;
    _f0 = *mTargetPos_d;
    sead::Vector3f position = mActor->getMtx().getTranslation();
    if (auto* body = mActor->getMainBody())
        body->getPosition(&position);
    _e4 = _f0 - position;
    _e4.normalize();
    _11c = mActor->getMtx().getTranslation();
    _149 = false;
    sub_71000A3400();
}

bool ArrowShootMove::sub_71000A331C() {
    auto* actor = mActor;
    if (!actor || !hasAttackInfo(actor))
        return false;
    auto* info = getAttackInfo(actor, 0);
    if (!info || sub_71000A50D0(info))
        return false;
    const sead::Vector3f position = info->_0;
    const sead::Vector3f direction = info->_c;
    const ksys::phys::MaterialMask material = info->_20;
    sub_71000A5254(direction, position, material, false);
    return true;
}

// NON_MATCHING: stack layout of the SafeString temporaries / matrix and the order of the two null tests.
void ArrowShootMove::sub_71000A3400() {
    ksys::phys::RigidBody* atk_body;
    if (auto* set = mActor->getPhysics()->findBodyByName(sead::SafeString(*sub_71007A24BC()))) {
        if (*mIsShootByPlayer_d)
            atk_body = set->getRigidBody(set->findBodyIndexByHavokName("AtkPlayerBody"));
        else
            atk_body = set->getRigidBody(set->findBodyIndexByHavokName("AtkEnemyBody"));
        _138 = atk_body;
    } else {
        atk_body = _138;
    }
    if (auto* main_body = mActor->getMainBody()) {
        if (atk_body) {
            sead::Matrix34f mtx;
            main_body->getTransform(&mtx);
            _138->setTransform(mtx);
            sub_71007A2B64(_138, nullptr);
            sub_71007A2EB0(_138, mActor, nullptr);
            _138->setContactNone();
            sub_71000A5604();
        }
    }
}

void ArrowShootMove::sub_71000A5604() {
    if (!mActor)
        return;
    if (!mActor->getPhysics()->findBodyByName(*sub_71007A24BC()))
        return;
    _a0 = *mAtAttr_d;
    _a4 = *mAtPoint_d;
    _ac = *mAtImpulse_d;
    _b0 = *mAtImpact_d;
    const s32 min_damage = *mAtMinDamage_d;
    auto* chemical = mActor->getChemicalStuff();
    if (chemical && (chemical->mMaterial->attribute.ref() & 0x10) && !_148)
        _a0 = 4;
    getActorAttackSensor(mActor)->activateAttackSensor(8, _a0 | 0x80, s32(_a4), s32(_ac), 0.0f,
                                                       s32(_b0), 1, -1, false, min_damage, -1);
    _a8 = *mAtRange_d;
}

void ArrowShootMove::m37() {
    auto* body = mActor->getMainBody();
    if (!body)
        return;

    _b4 += _fc;
    if (_fc < 0.0f)
        _b4.setToMax(_100);
    else if (_fc > 0.0f)
        _b4.setToMin(_100);
    _b4.updateStats();

    sead::Vector3f dir;
    m39(&dir);
    sead::Vector3f velocity = dir * _b4.value;
    if (act::DamageInfoMgr::sub_7100674764()) {
        const sead::Vector3f relative_velocity = *mRelativeVel_d;
        velocity += relative_velocity;
    }
    if (_140 == -1) {
        velocity.normalize();
        velocity *= 0.01f;
    }
    _110 = velocity;
    body->setLinearVelocity(velocity * 30.0f);
}

}  // namespace uking::action
