#include "Game/Actor/actEnemy.h"
#include <basis/seadNew.h>
#include <prim/seadScopedLock.h>
#include "Game/Actor/actRideable.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::act {

ksys::act::BaseProc* Enemy::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) Enemy(arg);
}

// NON_MATCHING: BoneHandle members (0xf68, 0x1010) are not typed yet; the original also skips the
// vtable store of the object at 0x1148
Enemy::~Enemy() = default;

void Enemy::Unk_12d0::sub_7100710F04() {}

bool Enemy::m57() {
    if (mActorFlags2.isOn(ActorFlag2::_40))
        return true;
    return _1290._38 > 0.0f;
}

bool Unk_7102357a08::m2(const ksys::Message& message) {
    if (message.getType() != 0x80000b0)
        return false;

    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_7102357a38::m2(const ksys::Message& message) {
    if (message.getType() != 0x80000af)
        return false;

    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_71023579d8::m2(const ksys::Message& message) {
    if (message.getType() != 0x80000cb)
        return false;

    auto* payload = static_cast<Unk_71023579d8_Payload*>(message.getUserData());
    if (!payload)
        return false;

    {
        sead::ScopedLock<sead::JobQueueLock> lock(&payload->mLock);
        _34._0 = payload->_0;
    }
    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_71023579a8::m2(const ksys::Message& message) {
    if (message.getType() != 0x80000d0)
        return false;

    auto* payload = static_cast<Unk_71023579a8_Payload*>(message.getUserData());
    if (!payload)
        return false;

    {
        sead::ScopedLock<sead::JobQueueLock> lock(&payload->mLock);
        _34._0 = payload->_0;
    }
    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_7102357978::m2(const ksys::Message& message) {
    if (message.getType() != 0x80000d1)
        return false;

    auto* payload = static_cast<Unk_7102357978_Payload*>(message.getUserData());
    if (!payload)
        return false;

    {
        sead::ScopedLock<sead::JobQueueLock> lock(&payload->mLock);
        _34._0 = payload->_0;
    }
    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_7102357948::m2(const ksys::Message& message) {
    if (message.getType() != 0x80000d2)
        return false;

    auto* payload = static_cast<Unk_7102357948_Payload*>(message.getUserData());
    if (!payload)
        return false;

    {
        sead::ScopedLock<sead::JobQueueLock> lock(&payload->mLock);
        _34._0 = payload->_0;
    }
    _30 = true;
    _18 = message.getSource();
    return true;
}

Unk_71023579d8::~Unk_71023579d8() = default;

Unk_71023579a8::~Unk_71023579a8() = default;

Unk_7102357978::~Unk_7102357978() = default;

Unk_7102357948::~Unk_7102357948() = default;

Unk_7100d3cd74* Enemy::m101() {
    return &_1128;
}

HorseRideInfo* Enemy::getPlayerRideInfo() {
    return _10f8;
}

ksys::act::Actor* Enemy::m31() {
    if (auto* rideable = getHorseOptionsMaybe())
        return rideable->sub_7100E8B644();
    return DynamicActor::m31();
}

ksys::act::Actor* Enemy::m48() {
    if (auto* rideable = getHorseOptionsMaybe())
        return rideable->sub_7100E8B6E0();
    return DynamicActor::m48();
}

Rideable* Enemy::getHorseOptionsMaybe() {
    return sead::DynamicCast<Rideable>(_1148._20);
}

RideableBase* Enemy::m132() {
    return _1148._20;
}

Unk_7100e8b2b8* Enemy::getMotorcyclePriorityStuffMaybe() {
    return sead::DynamicCast<Rideable>(_1148._20);
}

void Enemy::updateMtxFromPhysics() {
    sead::Vector3f velocity;
    sead::Matrix34f mtx;
    auto* controller = getCharacterController();
    if (controller && !_e84.isOnBit(11)) {
        controller->sub_7100F5F598(&velocity);
        mVelocity = velocity * (1.0f / 30.0f);
        controller->sub_7100F635BC(&velocity);
        mAngVelocity = velocity * (1.0f / 30.0f);
        controller->sub_7100F626E8(&mtx);
    } else {
        auto* body = mMainBody.load();
        if (!body)
            return;
        body->getLinearVelocity(&velocity);
        mVelocity = velocity * (1.0f / 30.0f);
        body->getAngularVelocity(&velocity);
        mAngVelocity = velocity * (1.0f / 30.0f);
        body->getTransform(&mtx);
    }
    mMtx = mtx;
    nullsub_4648();
}

}  // namespace uking::act
