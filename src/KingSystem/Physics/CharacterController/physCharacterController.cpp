#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/CharacterController/physCharacterControllerUnk40.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/physConversions.h"

namespace ksys::phys {

// Placeholder: object at CharacterController::_10 (only the field written by sub_7100F5EDE8).
struct CharacterControllerUnk10 {
    /* 0x00 */ u8 _0[0x30];
    /* 0x30 */ hkVector4f _30;
    /* 0x40 */ u8 _40[8];
    /* 0x48 */ f32 _48;
    /* 0x4c */ u8 _4c[0x70 - 0x4c];
    /* 0x70 */ f32 _70;
    /* 0x74 */ u8 _74[0x88 - 0x74];
    /* 0x88 */ f32 _88;
};

// Placeholder: object at CharacterController::_20.
struct CharacterControllerUnk20 {
    /* 0x00 */ u8 _0[0x40];
    /* 0x40 */ u32 _40;
    /* 0x44 */ u8 _44[0xc];
    /* 0x50 */ hkVector4f _50;
    /* 0x60 */ hkVector4f _60;
};

// Placeholder: 0x30 byte entry of the controller's shape list (CharacterControllerShapes).
struct CharacterControllerShape {
    /* 0x00 */ u8 _0[8];
    /* 0x08 */ void* _8;
    /* 0x10 */ bool _10;
    /* 0x11 */ u8 _11;
    /* 0x12 */ bool _12;
    /* 0x13 */ u8 _13;
    /* 0x14 */ f32 _14;
    /* 0x18 */ f32 _18;
    /* 0x1c */ f32 _1c;
    /* 0x20 */ sead::Vector3f _20;
    /* 0x2c */ u8 _2c[4];
};
KSYS_CHECK_SIZE_NX150(CharacterControllerShape, 0x30);

// Placeholder: object at CharacterController::_30.
struct CharacterControllerShapes {
    /* 0x00 */ void* _0;
    /* 0x08 */ sead::Buffer<CharacterControllerShape> mShapes;
};

// Placeholder: objects at CharacterController::_38 / _40 / _48 / _50 (only the fields read / written by the accessors).
struct CharacterControllerUnk38 {
    /* 0x00 */ u8 _0[0x34];
    /* 0x34 */ bool _34;
    /* 0x38 */ sead::Vector3f _38;
    /* 0x44 */ sead::Vector3f _44;
};


struct CharacterControllerUnk48 {
    /* 0x00 */ u8 _0[0x50];
    /* 0x50 */ u8 _50;
    /* 0x51 */ u8 _51[0x94 - 0x51];
    /* 0x94 */ u32 _94;
};

struct CharacterControllerUnk50 {
    /* 0x00 */ u8 _0[0x18];
    /* 0x18 */ f32 _18;
    /* 0x1c */ u8 _1c[0x38 - 0x1c];
    /* 0x38 */ u32 _38;
};

// NON_MATCHING: register assignment
void CharacterController::sub_7100F5E754(bool value) {
    _48->_50 = value;
}

void CharacterController::sub_7100F631E0(bool value) {
    _40->sub_7100F6693C(value);
}

f32 CharacterController::sub_7100F5EEE8() const {
    return _130;
}

void CharacterController::sub_7100F5E850(f32 value) {
    if (value <= 0.0f)
        return;
    _10->_88 = value;
}

// NON_MATCHING: the original moves the z component into s2 before y
sead::Vector3f CharacterController::sub_7100F5EE08() const {
    return toVec3(_10->_30);
}

void CharacterController::sub_7100F5EED4(f32 value) {
    _10->_70 = value;
}

void CharacterController::sub_7100F60368(f32 mass) {
    mRigidBody->setMass(mass);
}

void CharacterController::sub_7100F60378(f32 mass) {
    _138 = mass;
    mRigidBody->setMass(mass / _130);
}

void CharacterController::sub_7100F63178(const sead::Vector3f& a, const sead::Vector3f& b) {
    auto* unk = _38;
    unk->_34 = true;
    unk->_38 = a;
    unk->_44 = b;
}

void CharacterController::sub_7100F631B8(bool value) {
    _40->_10 = value;
    _40->sub_7100F6693C(value);
}

bool CharacterController::sub_7100F631CC() const {
    return _40->_10 == 1;
}

u8 CharacterController::sub_7100F63210() const {
    return _40->_70;
}

u8 CharacterController::sub_7100F6337C() const {
    return _40->_6e;
}

void CharacterController::sub_7100F5EEF0(f32 value) {
    _134 = value;
}

f32 CharacterController::sub_7100F5EEF8() const {
    return _134;
}

f32 CharacterController::sub_7100F60390() const {
    return _138;
}

f32 CharacterController::sub_7100F5EF88() const {
    return _30->mShapes[_224]._14;
}

f32 CharacterController::sub_7100F5EFB0() const {
    return _30->mShapes[_224]._14;
}

f32 CharacterController::sub_7100F5EFD8() const {
    return _30->mShapes[_224]._18;
}

f32 CharacterController::sub_7100F5F000() const {
    return _30->mShapes[_224]._1c;
}

f32 CharacterController::sub_7100F5F100() const {
    return _30->mShapes[_224]._18;
}

const sead::Vector3f& CharacterController::sub_7100F5F028() const {
    return _30->mShapes[_224]._20;
}

f32 CharacterController::sub_7100F5F050() const {
    return 0;
}

f32 CharacterController::sub_7100F5F058() const {
    return 1;
}

void CharacterController::sub_7100F5F060(const sead::Vector3f& value) {
    _ec = value;
}

bool CharacterController::sub_7100F5F128() const {
    return _116 & 1;
}

// NON_MATCHING: the original returns the byte without the bool conversion (but SimpleKokkoRoot::calc_ needs bool)
bool CharacterController::sub_7100F5F264() const {
    return _40->_69;
}

void CharacterController::sub_7100F60458() {
    _94.set(0, 0, 0);
}

// NON_MATCHING: store order / scheduling (the original stores the flag word last)
void CharacterController::sub_7100F6059C() {
    _116 &= 0xe3e3;
    _148 = 0;
    _144 = 1.0f;
    _15c = 0;
    _160 = 0;
    _168 = 0;
    _210 = 0;
    _214 = 0;
}

void CharacterController::sub_7100F605C8(const sead::Vector3f& value) {
    _a0.setTranslation(value);
}

u32 CharacterController::sub_7100F609D8() const {
    return _40->_64;
}

void CharacterController::sub_7100F60E80(bool value) {
    _50->_38 = value;
    _48->_94 = value;
}

f32 CharacterController::sub_7100F62B78() const {
    return _11c;
}

const sead::Vector3f& CharacterController::sub_7100F62B80() const {
    return _120;
}

void CharacterController::sub_7100F62B88(const sead::Vector3f& value) {
    _120 = value;
}

void CharacterController::sub_7100F62BA4(f32 value) {
    _50->_18 = value;
}

void CharacterController::sub_7100F62C14(f32 max_impulse) {
    mRigidBody->setMaxImpulse(max_impulse);
    if (_114 & 0x2000) {
        for (int i = 0; i < _288.size(); ++i) {
            if (auto* body = _288[i])
                body->setMaxImpulse(max_impulse);
        }
    }
}

f32 CharacterController::sub_7100F62CA0() const {
    return mRigidBody->getMaxImpulse();
}

bool CharacterController::sub_7100F62DC8() const {
    return mRigidBody->isEntityMotionFlag10Off();
}

void CharacterController::sub_7100F62E64(const sead::Vector3f& center) {
    mRigidBody->setCenterOfMassInLocal(center);
}

void CharacterController::sub_7100F62E6C(sead::Vector3f* center) const {
    mRigidBody->getCenterOfMassInLocal(center);
}

f32 CharacterController::sub_7100F62F58() const {
    return _218;
}

u8 CharacterController::sub_7100F63370() const {
    return _40->_6c;
}

void CharacterController::sub_7100F5E938(bool on) {
    mFlags.changeBit(15, on);
}

void CharacterController::sub_7100F631F4(bool on) {
    mFlags.changeBit(8, on);
}

// NON_MATCHING: the original selects the three flag updates with csel and different register assignment
void CharacterController::sub_7100F5E898() {
    if (_30->mShapes[_224]._10)
        _114 |= 0x400;
    else
        _114 &= ~0x400;
    if (_30->mShapes[_224]._11)
        _114 |= 0x800;
    else
        _114 &= ~0x800;
    if (_30->mShapes[_224]._12)
        _114 |= 0x1000;
    else
        _114 &= ~0x1000;
}

void CharacterController::sub_7100F5E95C(f32 scale) {
    _218 *= scale / mRigidBody->getScale();
    mRigidBody->setScale(scale);
    mRigidBody->updateShape();
    if (_298) {
        _298->setScale(scale);
        _298->updateShape();
    }
}

bool CharacterController::sub_7100F5ECC4() {
    for (int i = 0; i < _288.size(); ++i) {
        if (auto* body = _288[i]) {
            if (!body->removeFromWorldAndResetLinks())
                return false;
        }
    }
    return mRigidBody->removeFromWorldAndResetLinks();
}

void CharacterController::sub_7100F5EF30(f32 value) {
    const f32 max_velocity = (value > 1.0f ? 5.0f : 1.0f) * value * 100.0f;
    mRigidBody->setMaxLinearVelocity(max_velocity);
    _10->_48 = max_velocity;
}

void CharacterController::sub_7100F60794() {
    mRigidBody->resetFrozenState();
    if (_298)
        _298->resetFrozenState();
}

void CharacterController::sub_7100F60934(bool on) {
    mRigidBody->setEntityMotionFlag200(on);
    if (_114 & 0x2000) {
        for (int i = 0; i < _288.size(); ++i) {
            if (auto* body = _288[i])
                body->setEntityMotionFlag200(on);
        }
    }
}

void CharacterController::sub_7100F62D3C(bool on) {
    mRigidBody->setEntityMotionFlag8(on);
    if (_114 & 0x2000) {
        for (int i = 0; i < _288.size(); ++i) {
            if (auto* body = _288[i])
                body->setEntityMotionFlag8(on);
        }
    }
}

void CharacterController::sub_7100F603F8(const sead::Vector3f& delta) {
    if (delta.x != 0 || delta.y != 0 || delta.z != 0)
        _114 |= 0x20;
    _94 += delta;
}

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

void CharacterController::sub_7100F5EC44() {
    mFlags.reset(0x10000);
    _298 = nullptr;
    for (int i = 0; i < _288.size(); ++i) {
        if (auto* body = _288[i])
            body->removeFromWorld();
    }
    mRigidBody->removeFromWorld();
}

void CharacterController::sub_7100F60604() {
    mRigidBody->setContactNone();
    if (_250)
        _250->invoke(this);
}

void CharacterController::sub_7100F62BC0(bool fixed) {
    if (!fixed && (_114 & 2))
        return;
    mRigidBody->setFixed(Fixed(fixed), PreserveVelocities(false));
    mFlags.change(4, fixed);
}

void CharacterController::sub_7100F62CA8(bool clear) {
    mRigidBody->clearEntityMotionFlag4(clear);
    if (!(_114 & 0x2000))
        return;
    for (int i = 0; i < _288.size(); ++i) {
        if (auto* body = _288[i])
            body->clearEntityMotionFlag4(clear);
    }
}

void CharacterController::sub_7100F62DD0(f32 scale) {
    mRigidBody->setColImpulseScale(scale);
    if (!(_114 & 0x2000))
        return;
    for (int i = 0; i < _288.size(); ++i) {
        if (auto* body = _288[i])
            body->setColImpulseScale(scale);
    }
}

void CharacterController::sub_7100F63604(CollisionInfo* info) {
    if (!(_114 & 0x2000))
        return;
    for (int i = 0; i < _288.size(); ++i)
        _288[i]->setCollisionInfo(info);
}

CollisionInfo* CharacterController::sub_7100F6367C() const {
    if (!(_114 & 0x2000))
        return nullptr;
    auto* body = _288[0];
    if (!body)
        return nullptr;
    return body->getCollisionInfo();
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

f32 CharacterController::sub_7100F62E5C() const {
    return mRigidBody->getColImpulseScale();
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

void CharacterController::sub_7100F5FBC8(sead::Vector3f* linear_velocity,
                                         sead::Vector3f* angular_velocity,
                                         const sead::Matrix34f& target) {
    if (mFlags.isOn(0x10000))
        _298->computeVelocities(linear_velocity, angular_velocity, target);
    else
        mRigidBody->computeVelocities(linear_velocity, angular_velocity, target);
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

// NON_MATCHING: the two field addresses are computed in the opposite order (csel operands swapped), as in
// physicsXXXGetMtx_1
void CharacterController::sub_7100F626E8(sead::Matrix34f* out) const {
    (mFlags.isOn(0x10000) ? _298 : mRigidBody)->getTransform(out);
    *out = *out * _a0;
}

void CharacterController::sub_7100F63700(bool clear) {
    if (clear)
        mFlags.reset(0x40);
    else
        mFlags.set(0x40);
}

bool CharacterController::sub_7100F5E954() const {
    return mRigidBody->isAddedToWorld();
}

void CharacterController::sub_7100F5EDB4(SystemGroupHandler* handler) {
    mRigidBody->setSystemGroupHandler(handler);
}

void CharacterController::sub_7100F5EDBC(const sead::Vector3f& value) {
    _64.x = value.x;
    _64.y = value.y;
    _64.z = value.z;
}

void CharacterController::sub_7100F5EEE0(float value) {
    _220 = value;
}

void CharacterController::sub_7100F5EECC(f32 value) {
    _104 = value;
}

void CharacterController::sub_7100F5EDE8(const sead::Vector3f& value) {
    loadFromVec3(&_10->_30, value);
}

void CharacterController::sub_7100F6353C(sead::Vector3f* out) const {
    storeToVec3(out, _20->_60);
}

bool CharacterController::sub_7100F5F234(sead::Vector3f* out) const {
    if (!_20->_40)
        return false;
    if (out)
        storeToVec3(out, _20->_50);
    return true;
}

bool CharacterController::sub_7100F62EC0(f32* out, int index) const {
    auto& shape = _30->mShapes[index];
    if (!shape._8)
        return false;
    *out = shape._18;
    return true;
}

bool CharacterController::sub_7100F62E74(f32* out, int index) const {
    auto& shape = _30->mShapes[index];
    if (!shape._8 || !shape._10)
        return false;
    *out = shape._14;
    return true;
}

bool CharacterController::sub_7100F62EFC(sead::Vector3f* out, int index) const {
    auto& shape = _30->mShapes[index];
    if (!shape._8 || !shape._12)
        return false;
    *out = shape._20;
    return true;
}

RigidBodyAccessor* CharacterController::sub_7100F635C4() const {
    return mRigidBody->getRigidBodyAccessor();
}

void CharacterController::sub_7100F63554(bool clear) {
    if (clear)
        mRigidBody->resetFlag1000000();
    else
        mRigidBody->setFlag1000000();
}

void CharacterController::sub_7100F636B0(bool clear) {
    if (clear)
        mRigidBody->resetFlag200();
    else
        mRigidBody->setFlag200();
}

void CharacterController::sub_7100F5EF08(bool on) {
    mFlags.changeBit(0, on);
    _114 |= 0x20;
}

// NON_MATCHING: the two field addresses are computed in the opposite order (csel operands swapped), as in
// physicsXXXGetMtx_1
void CharacterController::sub_7100F5F6E0(sead::Vector3f* position) const {
    (mFlags.isOn(0x10000) ? _298 : mRigidBody)->getPosition(position);
}

void CharacterController::sub_7100F5F6FC(const sead::Vector3f& velocity) {
    sub_7100F5F774(velocity, true, false);
    if (mFlags.isOn(0x10000))
        _298->setLinearVelocity(velocity);
    if (velocity.x != 0.0f || velocity.y != 0.0f || velocity.z != 0.0f)
        _114 |= 0x20;
}

void CharacterController::sub_7100F5FB24(const sead::Vector3f& angular_velocity) {
    mRigidBody->setAngularVelocity(angular_velocity);
    if (mFlags.isOn(0x10000))
        _298->setAngularVelocity(angular_velocity);
    if (angular_velocity.x != 0.0f || angular_velocity.y != 0.0f || angular_velocity.z != 0.0f)
        _114 |= 0x20;
}

void CharacterController::sub_7100F60398(const sead::Vector3f& impulse) {
    if (impulse.x != 0.0f || impulse.y != 0.0f || impulse.z != 0.0f)
        _114 |= 0x20;
    _88 += impulse;
}

}  // namespace ksys::phys
