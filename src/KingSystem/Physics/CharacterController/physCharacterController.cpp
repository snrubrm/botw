#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::phys {

void CharacterController::sub_7100F5EDD8(float value) {
    _fc = value;
}

void CharacterController::sub_7100F5EDE0(float value) {
    _100 = value;
}

void CharacterController::sub_7100F5EEB8(float value) {
    _114 |= 0x20;
    _110 = value;
}

float CharacterController::sub_7100F5EF00() const {
    return _60;
}

void CharacterController::sub_7100F5F598(sead::Vector3f* velocity) const {
    mRigidBody->getLinearVelocity(velocity);
}

float CharacterController::sub_7100F60370() const {
    return mRigidBody->getMass();
}

RigidBody* CharacterController::sub_7100F61A34() const {
    return mRigidBody;
}

void CharacterController::sub_7100F62B70(float value) {
    _11c = value;
}

void CharacterController::sub_7100F62BB0() {
    sub_7100F5F270(1);
}

void CharacterController::sub_7100F5EC30() {
    if (!mFlags.isOn(0x10000))
        mRigidBody->addToWorld();
}

void CharacterController::enableContactLayer(ContactLayer layer) {
    mRigidBody->enableContactLayer(layer);
}

void CharacterController::sub_7100F605F0() {
    mRigidBody->setContactAll();
}

void CharacterController::disableContactLayer(ContactLayer layer) {
    mRigidBody->disableContactLayer(layer);
}

void CharacterController::sub_7100F5E764(bool clear) {
    mRigidBody->clearEntityMotionFlag10(clear);
    if (!(_114 & 0x2000))
        return;
    for (int i = 0; i < _288.size(); ++i) {
        if (auto* body = _288[i])
            body->clearEntityMotionFlag10(clear);
    }
}

void CharacterController::sub_7100F62BB8() {
    sub_7100F5F270(0);
}

bool CharacterController::sub_7100F635B4() const {
    return mRigidBody->isAddingBodyToWorld();
}

void CharacterController::sub_7100F635BC(sead::Vector3f* velocity) const {
    mRigidBody->getAngularVelocity(velocity);
}

void CharacterController::sub_7100F635D0(ContactPointInfo* info) {
    mRigidBody->setContactPointInfo(info);
}

ContactPointInfo* CharacterController::sub_7100F635D8() const {
    return mRigidBody->getContactPointInfo();
}

ContactPointInfo* CharacterController::sub_7100F635E4() const {
    return mRigidBody->getContactPointInfo();
}

void CharacterController::sub_7100F635F0(CollisionInfo* info) {
    mRigidBody->setCollisionInfo(info);
}

CollisionInfo* CharacterController::sub_7100F635F8() const {
    return mRigidBody->getCollisionInfo();
}

void CharacterController::sub_7100F636A8(f32 factor) {
    mRigidBody->setMagneMassScalingFactor(factor);
}

bool CharacterController::sub_7100F636EC() const {
    return !mRigidBody->hasFlag(RigidBody::Flag::_200);
}

bool CharacterController::sub_7100F63590() const {
    return !mRigidBody->hasFlag(RigidBody::Flag::_1000000) &&
           !mRigidBody->hasFlag(RigidBody::Flag::FixedWithImpulsePreserved);
}

bool CharacterController::sub_7100F62D34() const {
    return mRigidBody->isEntityMotionFlag4Off();
}

void CharacterController::sub_7100F5EE1C(const sead::Vector3f& value) {
    if (_114 & 4)
        return;
    _70 = value;
    const f32 length = _70.length();
    if (length > 0.0f) {
        _7c.setScale(_70, 1.0f / length);


    }
}

// NON_MATCHING: the original folds the null check of `body` into the ccmp chain (we branch on it)
bool CharacterController::sub_7100F5F270(int idx) {
    bool force = false;
    if (mFlags.isOn(0x10000)) {
        force = true;
        if (_224 != idx && idx < _288.size()) {
            auto* body = _288[idx];
            if (body && body != _298 && _298) {




                sead::Matrix34f mtx;
                _298->getTransform(&mtx);
                _298->removeFromWorld();
                _224 = idx;
                _298 = body;
                body->setTransform(mtx);
                _298->addToWorld();
            }
        }
    }
    return sub_7100F5F344(idx, force);
}

// NON_MATCHING: body selection becomes a csel of the two field addresses (as in
// physicsXXXGetMtx_1); the original branches on the flag byte
void CharacterController::sub_7100F5FC8C(const sead::Matrix34f& mtx) {
    sead::Vector3f linear_vel;
    sead::Vector3f angular_vel;
    RigidBody* body;
    if (mFlags.isOn(0x10000))
        body = _298;
    else
        body = mRigidBody;
    body->computeVelocities(&linear_vel, &angular_vel, mtx);


    mRigidBody->setAngularVelocity(angular_vel);
    if (mFlags.isOn(0x10000))
        _298->setAngularVelocity(angular_vel);
    if (angular_vel.x != 0.0f || angular_vel.y != 0.0f || angular_vel.z != 0.0f)
        _114 |= 0x20;
}

// NON_MATCHING: the two field addresses are computed in the opposite order (csel operands swapped)
void CharacterController::physicsXXXGetMtx_1(sead::Matrix34f* mtx) const {
    (mFlags.isOn(0x10000) ? _298 : mRigidBody)->getTransform(mtx);
}

void CharacterController::sub_7100F63700(bool clear) {
    if (clear)
        mFlags.reset(0x40);
    else
        mFlags.set(0x40);
}

}  // namespace ksys::phys
