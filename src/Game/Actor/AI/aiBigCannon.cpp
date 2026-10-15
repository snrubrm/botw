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
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/System/VFR.h"
#include "Game/Actor/aiUnk_710072BA90.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
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

// NON_MATCHING: source combines the native velocity/transform loops; matrix and handle scheduling differ.
void BigCannon::calc_() {
    auto* actor = mActor;
    f32 target = _fc;
    if (actor->hasPlacementLinkWithTypeAxisY()) {
        const bool signal = actor->checkAxisYSignal();
        f32 speed = sead::Mathf::deg2rad(*mTiltAngularSpeed_m);
        f32 acceleration = *mRotRadAccel_s;
        if (signal) {
            target = _f8;
            if (_104 < 0.0f) {
                acceleration = *mRotBrake_s;
                speed = 0.0f;
            }
        } else if (_104 > 0.0f) {
            acceleration = *mRotBrake_s;
            speed = 0.0f;
        } else {
            speed = -speed;
        }
        ksys::VFR::chase(&_104, speed, acceleration);
        const f32 tilt = *mTiltAngle_m;
        const f32 delta = _104 * ksys::VFR::instance()->getDeltaFrame();
        _100 += tilt < 0.0f ? -delta : delta;
        bool moving;
        if (signal != (tilt < 0.0f)) {
            if (_100 > target)
                _100 = target;
            moving = !(_100 >= target);
        } else {
            if (_100 < target)
                _100 = target;
            moving = !(_100 <= target);
        }
        if (moving) {
            _10a = false;
            _10b = true;
            if (!_c8.sub_7101241AD8(1))
                xlinkSearchAndEmit(actor, "Rotate", 1, &_c8);
        } else {
            _104 = 0.0f;
            if (_10b) {
                xlinkSearchAndEmit(actor, "RotateStop", 1, nullptr);
                _10b = false;
            }
            if (_c8.sub_7101241AD8(1))
                _c8.fadeXLink();
        }
        auto* bodies = actor->getRigidBodyByName(sub_71007A24E4()->cstr());
        sead::Matrix34f transform;
        actor->getHomeMtx(&transform);
        sead::Matrix34f rotation;
        rotation.makeR(_e8 * _100);
        transform *= rotation;
        if (bodies) {
            const s32 count = bodies->getRigidBodies().size();
            for (s32 i = 0; i < count; ++i) {
                auto* body = bodies->getRigidBody(i);
                if (!body)
                    continue;
                if (_10a) {
                    body->setLinearVelocity(sead::Vector3f::zero, sead::Mathf::epsilon());
                    body->setAngularVelocity(sead::Vector3f::zero, sead::Mathf::epsilon());
                } else {
                    body->changePositionAndRotation(transform, sead::Mathf::epsilon());
                }
            }
        }
        if (!moving)
            _10a = true;
    }
    bool create = !_b8.isAllocatedOrFailed();
    if (!create) {
        if (_b8.isProcReady()) {
            _109 = true;
        } else if (_b8.hasProcCreationFailed()) {
            _b8.deleteProcIfFailed();
            create = true;
        }
    }
    if (create) {
        ksys::act::InstParamPack pack;
        ksys::act::ActorCreator::setCreatePriorityState1(pack, mActor);
        ksys::act::ActorCreator::instance()->requestCreateActor(
            mActName_s.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &_b8,
            &pack, nullptr, 1);
    }
    _108 = false;
    _f4 = -1;
    actor->getAtk();
    if (auto* damage = sub_710072BA90(actor))
        _f4 = damage->getField54();
    if (_109 && _f4 == 4)
        _108 = true;
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
