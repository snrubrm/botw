#include "Game/Actor/AI/aiBigCannon.h"
#include <math/seadMathCalcCommon.h>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::ai {

BigCannon::BigCannon(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BigCannon::~BigCannon() {
    if (auto* physics = mActor->getPhysics())
        physics->sub_7100FB835C();
}

bool BigCannon::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void BigCannon::enter_(ksys::act::ai::InlineParamPack* params) {
    _f8 = sead::Mathf::deg2rad(*mTiltAngle_m) + 0.0f;
    auto* actor = mActor;
    _fc = 0;
    _104 = 0;
    _108 = false;
    _109 = false;

    ksys::act::InstParamPack pack;
    ksys::act::ActorCreator::setCreatePriorityState1(pack, actor);
    ksys::act::ActorCreator::instance()->requestCreateActor(
        mActName_s.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &_b8, &pack,
        nullptr, 1);

    if (auto* body = actor->getRigidBodyByName(sub_71007A2520()->cstr())) {
        body->addToWorld();
        body->setSystemGroupHandler(nullptr, ksys::phys::ContactLayerType::Entity);
    }
    _10a = false;
    _10b = false;
}

// NON_MATCHING: vector load/store scheduling, float registers and branch layout differ.
void BigCannon::sub_710032D5FC() {
    auto* actor = mActor;
    auto* model = actor->getModel();
    sead::Matrix34f transform = actor->getMtx();
    sead::Vector3f position = actor->getMtx().getTranslation();
    if (mShotNodeName_s.isEmpty()) {
        sead::Vector3f offset;
        offset.setRotated(transform, *mOffset_s);
        position += offset;
    } else if (model) {
        const auto bone = model->searchBone(mShotNodeName_s);
        if (bone.isValid()) {
            model->getUnits()(bone.model_unit_index)->mModelUnit->getBoneWorldMatrix(&transform,
                                                                                  bone.bone_index);
            transform.getTranslation(position);
        }
    }
    _10c = position;
    sead::Vector3f velocity;
    if (!*mIsUseShotNodeAngle_s) {
        transform = actor->getMtx();
        transform.setTranslation(position);
        const f32 angle = sead::Mathf::deg2rad(_12c ? _124 : *mAngle_m);
        sead::Vector3f front;
        front.setRotated(transform, {0.0f, std::sin(angle), std::cos(angle)});
        front.normalize();
        sead::Vector3f up = front.cross(sead::Vector3f::ex);
        up.normalize();
        sead::Matrix33f basis;
        basis.setBase(0, sead::Vector3f::ex);
        basis.setBase(1, up);
        basis.setBase(2, front);
        velocity = sead::Vector3f::zero;
        velocity.z = *mSpeed_m;
        if (_12c)
            velocity.z = _128 / 30.0f;
        velocity.rotate(basis);
    } else {
        transform.setTranslation(position);
        velocity = transform.getBase(2) * (_12c ? _128 / 30.0f : *mSpeed_m);
    }
    _118 = _10c + velocity;
    m34(transform, &velocity);
}

void BigCannon::leave_() {
    _b8.deleteProc();
}

void BigCannon::loadParams_() {
    getStaticParam(&mRotRadAccel_s, "RotRadAccel");
    getStaticParam(&mRotBrake_s, "RotBrake");
    getStaticParam(&mShotCannonBallScale_s, "ShotCannonBallScale");
    getStaticParam(&mIsDrawDebug_s, "IsDrawDebug");
    getStaticParam(&mIsUseShotNodeAngle_s, "IsUseShotNodeAngle");
    getStaticParam(&mActName_s, "ActName");
    getStaticParam(&mShotNodeName_s, "ShotNodeName");
    getStaticParam(&mOffset_s, "Offset");
    getMapUnitParam(&mTiltAngle_m, "TiltAngle");
    getMapUnitParam(&mTiltAngularSpeed_m, "TiltAngularSpeed");
    getMapUnitParam(&mAngle_m, "Angle");
    getMapUnitParam(&mSpeed_m, "Speed");
    getMapUnitParam(&mActorName_m, "ActorName");
}

void BigCannon::m35(ksys::act::Actor* actor, ksys::act::Actor* ball) {}

void BigCannon::m36(ksys::act::Actor* ball) {}

// NON_MATCHING: the original loads mActor (for m35) before releasing the handle (see the lane1 log)
void BigCannon::m34(const sead::Matrix34f& mtx, const sead::Vector3f* vel) {
    auto* ball = sead::DynamicCast<ksys::act::Actor>(_b8.releaseAndWakeProc());
    if (!ball)
        return;

    ball->setMtx(mtx, true, true);
    ball->nullsub_4648();
    const f32 scale = *mShotCannonBallScale_s;
    ball->setScale({scale, scale, scale});
    ball->setVelocity(vel, nullptr);
    m35(mActor, ball);
    m36(ball);
}

}  // namespace uking::ai
