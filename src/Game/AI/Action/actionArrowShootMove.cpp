#include "Game/AI/Action/actionArrowShootMove.h"
#include "Game/Damage/dmgInfoManager.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"

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

void ArrowShootMove::calc_() {
    ksys::act::ai::Action::calc_();
}

float ArrowShootMove::m32() {
    return 0.5f;
}

bool ArrowShootMove::m35(const ksys::act::ActorConstDataAccess& accessor) {
    return false;
}

void ArrowShootMove::m36(bool* out, const ksys::act::ActorConstDataAccess& accessor) {}

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

// NON_MATCHING: scheduling only (the original loads *mRelativeVel_d z before the adds and adds the squares of the
// normalisation in the other operand order)
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
    if (dmg::DamageInfoMgr::sub_7100674764())
        velocity += *mRelativeVel_d;
    if (_140 == -1) {
        velocity.normalize();
        velocity *= 0.01f;
    }
    _110 = velocity;
    body->setLinearVelocity(velocity * 30.0f);
}

}  // namespace uking::action
