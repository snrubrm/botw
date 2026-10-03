#include "Game/AI/AI/aiSiteBossChemicalProjectile.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

SiteBossChemicalProjectile::SiteBossChemicalProjectile(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

SiteBossChemicalProjectile::~SiteBossChemicalProjectile() {
    if (mIsSetParentSystemGroupHandler_s && *mIsSetParentSystemGroupHandler_s) {
        if (auto* physics = mActor->getPhysics())
            physics->sub_7100FB835C();
    }
}

bool SiteBossChemicalProjectile::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SiteBossChemicalProjectile::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SiteBossChemicalProjectile::leave_() {
    ksys::act::ai::Ai::leave_();
}

bool SiteBossChemicalProjectile::handleMessage_(const ksys::Message* message) {
    if (!message || message->getBrokerId() != u32(-1))
        return false;

    if (message->getType() == 0x800003a) {
        if (!message->getUserData())
            return false;
        auto* payload = static_cast<SiteBossProjectilePayload*>(message->getUserData());
        _f0 = payload->_0;
        _108 = payload->_18;
        _118 = payload->_28;
        _d6 = true;
        return true;
    }
    if (message->getType() == 0x800004d) {
        auto* payload = static_cast<uking::act::SiteBoss::Unk_71002cf2ac::Payload*>(
            message->getUserData());
        if (payload->owner) {
            _158.acquire(payload->owner, false);
            if (auto* boss = sead::DynamicCast<uking::act::SiteBoss>(payload->owner))
                boss->_1560._9c &= ~(1u << payload->idx);
        }
        _d8 = true;
        return true;
    }
    if (message->getType() == 0x8000004) {
        _d9 = true;
        return true;
    }
    return false;
}

// NON_MATCHING: the no-body path (`_bc *= -rate`) ends with a shared `str z` and an `stp` of x/y in the
// original; ours schedules the z load between the two stores
void SiteBossChemicalProjectile::m44() {
    if (!(getAttackInfo(mActor, 0)->_18 & 0xa)) {
        SiteBossChemicalProjectile::m42();
        return;
    }

    sub_71003EA0AC(false);
    if (auto* body = mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkBody")) {
        sead::Vector3f position;
        body->getPosition(&position);
        const f32 reflect_speed = _bc.length() * *mReflectSpeedRate_s;
        _bc = _b0 - position;
        _bc.normalize();
        _bc *= reflect_speed;
    } else {
        _bc *= -*mReflectSpeedRate_s;
    }
    _e0 *= *mReflectSpeedRate_s;
    _118 = *mReflectSpeedRate_s * _118;
    _178 = *mExplosionTime_s;
    _d4 = true;
}

void SiteBossChemicalProjectile::loadParams_() {
    getStaticParam(&mExplosionTime_s, "ExplosionTime");
    getStaticParam(&mChaseAngleLimit_s, "ChaseAngleLimit");
    getStaticParam(&mReflectSpeedRate_s, "ReflectSpeedRate");
    getStaticParam(&mIsForceDelete_s, "IsForceDelete");
    getStaticParam(&mIsAdjustHeight_s, "IsAdjustHeight");
    getStaticParam(&mIsSetParentSystemGroupHandler_s, "IsSetParentSystemGroupHandler");
    getStaticParam(&mIsSetBindSpeed_s, "IsSetBindSpeed");
    getStaticParam(&mIsIgnoreObject_s, "IsIgnoreObject");
    getStaticParam(&mBindNodeName_s, "BindNodeName");
    getMapUnitParam(&mAttackPower_m, "AttackPower");
    getMapUnitParam(&mAtMinDamage_m, "AtMinDamage");
    getMapUnitParam(&mScaleTime_m, "ScaleTime");
    getMapUnitParam(&mRange_m, "Range");
    getMapUnitParam(&mAtkRadiusMax_m, "AtkRadiusMax");
}

const sead::SafeString& SiteBossChemicalProjectile::m34() {
    return mBindNodeName_s;
}

sead::Vector3f SiteBossChemicalProjectile::m35() {
    return {0.0f, 2.0f, 0.0f};
}

sead::Vector3f SiteBossChemicalProjectile::m36() {
    return sead::Vector3f::ones;
}

void SiteBossChemicalProjectile::m37() {}

void SiteBossChemicalProjectile::m38() {
    auto* main_body = mActor->getMainBody();
    if (!main_body)
        return;

    f32 scale = main_body->getScale();
    if (!sead::Mathf::equalsEpsilon(scale, *mAtkRadiusMax_m)) {
        sead::Mathf::chase(&scale, *mAtkRadiusMax_m, 1.0f / *mScaleTime_m);
        main_body->setScale(scale);
    }

    auto* atk_body = mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkBody");
    if (atk_body && !sead::Mathf::equalsEpsilon(atk_body->getScale(), *mAtkRadiusMax_m))
        atk_body->setScale(scale);

    mActor->setScale({scale, scale, scale});
}

bool SiteBossChemicalProjectile::m39() {
    return true;
}

bool SiteBossChemicalProjectile::m40() {
    return _d9;
}

bool SiteBossChemicalProjectile::m41() {
    return false;
}

void SiteBossChemicalProjectile::m42() {
    sub_71003EB688();
    auto* actor = mActor;
    if (auto* body = actor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkBody"))
        body->setLinearVelocity(sead::Vector3f::zero);
    if (auto* body = mActor->getMainBody())
        body->setLinearVelocity(sead::Vector3f::zero);
}

void SiteBossChemicalProjectile::sub_71003EB688() {
    ksys::act::ai::InlineParamPack params;
    params.addBool(m55(), "IsPlayerAttack", -1);
    params.addInt(*mAttackPower_m, "AttackPower", -1);
    params.addInt(*mAtMinDamage_m, "AtMinDamage", -1);
    if (_d5) {
        changeChild("爆発", &params);
    } else {
        _d5 = true;
        changeChild("反射後爆発", &params);
    }
}

void SiteBossChemicalProjectile::sub_71003EA0AC(bool a) {
    auto* body = mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkBody");
    if (!a)
        body = mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkPlayerBody");
    if (!body)
        return;

    const u32 attack_type = m50();
    u32 attack_attr = m51();
    if (auto* chemical = mActor->getChemicalStuff()) {
        if (chemical->_c0 == 2)
            attack_attr |= 0x200;
    }
    const sead::Matrix34f mtx = mActor->getMtx();
    body->setTransform(mtx);
    if (!body->isAddedToWorld())
        body->addToWorld();
    m52(body);
    getActorAttackSensor(mActor)->activateAttackSensor(attack_type, attack_attr, *mAttackPower_m, 0,
                                                       0.0f, 0, 1, -1, false, *mAtMinDamage_m, -1);
}

void SiteBossChemicalProjectile::sub_71003EA21C(bool a) {
    if (auto* parent = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcParent())) {
        if (a && !_158.hasProc())
            _158.acquire(parent, false);
        mActor->resetConnectedCalcParent(false);
    }
}

void SiteBossChemicalProjectile::m43(bool a) {}

const sead::Vector3f& SiteBossChemicalProjectile::m45() {
    return _bc;
}

void SiteBossChemicalProjectile::m46(const sead::Vector3f& v) {
    _bc = v;
    _118 = v.length();
}

void SiteBossChemicalProjectile::m47(f32 v) {
    _dc = v;
}

const sead::Vector3f& SiteBossChemicalProjectile::m48() {
    return _c8;
}

void SiteBossChemicalProjectile::m49(const sead::Vector3f& v) {
    _c8 = v;
}

u32 SiteBossChemicalProjectile::m50() {
    return 0x800;
}

u32 SiteBossChemicalProjectile::m51() {
    return 4;
}

void SiteBossChemicalProjectile::m52(ksys::phys::RigidBody* body) {
    sub_71007A2B64(body, nullptr);
    sub_71007A2EB0(body, mActor, nullptr);
}

void SiteBossChemicalProjectile::m53(ksys::phys::RigidBody* body) {
    body->setContactNone();
    body->enableContactLayer(ksys::phys::ContactLayer(3));
    body->enableContactLayer(ksys::phys::ContactLayer(4));
    body->enableContactLayer(ksys::phys::ContactLayer(5));
}

bool SiteBossChemicalProjectile::m54() {
    return *mIsAdjustHeight_s && !m55();
}

bool SiteBossChemicalProjectile::m55() {
    return _d4;
}

bool SiteBossChemicalProjectile::m56() {
    return !m55();
}

f32 SiteBossChemicalProjectile::m57() {
    return *mChaseAngleLimit_s;
}

}  // namespace uking::ai
