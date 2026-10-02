#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::phys {

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

}  // namespace ksys::phys
