#include "Game/Actor/actGelEnemy.h"
#include <basis/seadNew.h>
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGelEnemy.h"

namespace uking::act {

GelEnemy::GelEnemy(const CreateArg& arg) : Enemy(arg) {}

ksys::act::BaseProc* GelEnemy::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) GelEnemy(arg);
}

GelEnemy::~GelEnemy() = default;

void GelEnemy::preDelete2_(const PreDeleteArg& arg) {
    _1668.freeBuffer();
    Enemy::preDelete2_(arg);
}

void GelEnemy::m63() {
    Enemy::m63();

    if (auto* body = findPhysicsBodyByName(sub_71007A250C()->cstr(), "BgSensor")) {
        if (!body->isAddedToWorld()) {
            body->addToWorld();
            body->setContactAll();
            body->setFlag1000000();
            body->setFlag200();
        }
    }

    for (f32& value : _1644)
        value = std::numeric_limits<f32>::quiet_NaN();
    _1678 = 0;
}

void GelEnemy::initMaybe() {
    Enemy::initMaybe();

    const auto* gel = getParam()->getRes().mGParamList->getGelEnemy();
    auto* model = mModel;
    _1570.search(model, gel->mBodyRootBoneName.ref());
    _15e0.search(model, gel->mRightEyeBoneName.ref());
    _15a8.search(model, gel->mLeftEyeBoneName.ref());

    if (!gel->mMoveBoneName.ref().isEmpty()) {
        sub_71011DA868(&_14c8);
        _14c8.setName(gel->mMoveBoneName.ref());
        boneHandleStuff(&_14c8, false);
    }

    _1620.x = gel->mEyeUpMoveRate.ref();
    _1620.y = gel->mEyeDownMoveRate.ref();
    _1620.z = 0.0f;
    mMtx.getTranslation(_162c);
    _1638 = _162c;
    _165c = 0.0f;
    _1660 = 0.0f;
    _1664 = 1.0f;
}

bool GelEnemy::m81(const ksys::Message& message) {
    if (message.getType() == 0x3000003 || message.getType() == 0x3000004) {
        _1644[0] = _1644[1] = std::numeric_limits<f32>::quiet_NaN();
        _1644[2] = _1644[3] = std::numeric_limits<f32>::quiet_NaN();
        _1644[4] = _1644[5] = std::numeric_limits<f32>::quiet_NaN();
    }
    return Enemy::m81(message);
}

bool GelEnemy::startPreparingForPreDelete_() {
    sub_71011DA868(&_14c8);
    return Enemy::startPreparingForPreDelete_();
}

}  // namespace uking::act
