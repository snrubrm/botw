#include "Game/AI/AI/aiGoronCannonBase.h"
#include "KingSystem/ActorSystem/actActor.h"
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
    ksys::act::ai::Ai::enter_(params);
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
