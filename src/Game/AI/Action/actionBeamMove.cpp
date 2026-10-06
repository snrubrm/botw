#include "Game/AI/Action/actionBeamMove.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"

namespace uking::action {

BeamMove::BeamMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BeamMove::~BeamMove() = default;

bool BeamMove::init_(sead::Heap* heap) {
    _50 = mActor->getMainBody();
    _58 = mActor->findPhysicsBodyByName("Atk", "AtkBody");
    _60 = mActor->findPhysicsBodyByName("Atk", "AtkExplode");
    if (!_50 || !_58)
        return false;
    _50->enableContactLayer(ksys::phys::ContactLayer::EntityNPC);
    _50->enableContactLayer(ksys::phys::ContactLayer::EntityRagdoll);
    return true;
}

void BeamMove::enter_(ksys::act::ai::InlineParamPack* params) {
    m40();
    _68 = 0;
    _69 = 0;
    _6a = false;
    _6b = false;
    _6c = 0;
    const sead::Matrix34f mtx = mActor->getMtx();
    _50->setTransform(mtx);
    _58->setTransform(mtx);
    const sead::Vector3f velocity = _40 * _4c;
    _50->setLinearVelocity(velocity, sead::Mathf::epsilon());
    _50->setGravityFactor(0);
    _58->setLinearVelocity(velocity, sead::Mathf::epsilon());
    if (_60) {
        _60->setTransform(mtx);
        _60->setLinearVelocity(velocity, sead::Mathf::epsilon());
    }
    if (getActorAttackSensor(mActor)) {
        getActorAttackSensor(mActor)->activateAttackSensor(
            0x1000, m43(), m41(),
            mActor->getParam()->getRes().mGParamList->getAttack()->mImpulseLarge.ref(), 0.0f,
            mActor->getParam()->getRes().mGParamList->getAttack()->mGuardBreakPower.ref(),
            *mShieldDamage_s, -1, false, *mAtMinDamage_s, m42());
    }
    if (auto* info = _50->getContactPointInfo())
        info->subscribeLayer(ksys::phys::ContactLayer::EntityNPC);
    mFlags.reset(Flag::Changeable);
}

void BeamMove::sub_71000C1258() {
    const sead::Vector3f velocity = _40 * _4c;
    _50->setLinearVelocity(velocity, sead::Mathf::epsilon());
    _58->setLinearVelocity(velocity, sead::Mathf::epsilon());
}

void BeamMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void BeamMove::loadParams_() {
    getStaticParam(&mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mShieldDamage_s, "ShieldDamage");
    getStaticParam(&mForceExplodeFrame_s, "ForceExplodeFrame");
    getAITreeVariable(&mIsReflectThrownBullet_a, "IsReflectThrownBullet");
}

void BeamMove::calc_() {
    ksys::act::ai::Action::calc_();
}

bool BeamMove::m32(const AttackInfo* info) {
    return info->_18 & 0xa;
}

bool BeamMove::m34(const AttackInfo* info) {
    return info->_18 & 1;
}

void BeamMove::m35(sead::Vector3f* dir) {
    *dir = -_40;
}

void BeamMove::m36(const AttackInfo* info) {
    if (!info)
        return;

    sead::Matrix34f mtx;
    _50->getTransform(&mtx);
    mtx.setTranslation(info->_0);
    _50->setTransform(mtx);
    _58->setTransform(mtx);
    _50->setLinearVelocity(sead::Vector3f::zero);
    _58->setLinearVelocity(sead::Vector3f::zero);
    if (_60) {
        _60->setTransform(mtx);
        _60->setLinearVelocity(sead::Vector3f::zero);
    }
    setFinished();
}

f32 BeamMove::m37() {
    return 0.3f;
}

bool BeamMove::m38() {
    if (_6a)
        return false;

    sead::Vector3f pos;
    if (!m39(&pos))
        return false;

    _6a = true;
    sead::Matrix34f mtx;
    _50->getTransform(&mtx);
    mtx.setTranslation(pos);
    _50->changePositionAndRotation(mtx);
    _58->changePositionAndRotation(mtx);
    if (_60)
        _60->changePositionAndRotation(mtx);
    return true;
}

void BeamMove::m40() {
    _40 = mActor->getVelocity();
    _4c = _40.normalize() * 30.0f;
}

int BeamMove::m41() {
    return mActor->getParam()->getRes().mGParamList->getAttack()->mPower.ref();
}

int BeamMove::m42() {
    return mActor->getParam()->getRes().mGParamList->getAttack()->mPowerForPlayer.ref();
}

int BeamMove::m43() {
    return 2;
}

bool BeamMove::isFinished() const {
    if (hasAttackInfo(mActor) && (getAttackInfo(mActor, 0)->_18 & 0xb))
        return ksys::act::ai::Action::isFinished();

    auto* info = _50->getContactPointInfo();
    if (!info || info->getNumContactPoints() == 0 || info->begin().isEnd()) {
        if (!ksys::act::ai::Action::isFinished())
            return false;
    }

    if (_6b)
        return true;

    if (_60) {
        sead::Matrix34f mtx;
        _50->getTransform(&mtx);
        _60->setTransform(mtx);
        _60->setLinearVelocity(sead::Vector3f::zero);
    }
    _6b = true;
    return true;
}

}  // namespace uking::action
