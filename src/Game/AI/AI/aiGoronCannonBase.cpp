#include "Game/AI/AI/aiGoronCannonBase.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::ai {

GoronCannonBase::GoronCannonBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GoronCannonBase::~GoronCannonBase() {
    if (auto* physics = mActor->getPhysics())
        physics->sub_7100FB835C();
}

bool GoronCannonBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GoronCannonBase::enter_(ksys::act::ai::InlineParamPack* params) {
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

void GoronCannonBase::leave_() {
    _b8.deleteProc();
}

void GoronCannonBase::loadParams_() {
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

void GoronCannonBase::m35(ksys::act::Actor* actor, ksys::act::Actor* ball) {}

void GoronCannonBase::m36(ksys::act::Actor* ball) {}

}  // namespace uking::ai
