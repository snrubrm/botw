#include "Game/AI/Action/actionGearRotate.h"
#include <xlink2/xlink2Handle.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

GearRotate::GearRotate(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GearRotate::~GearRotate() {
    if (_70) {
        delete _70;
        _70 = nullptr;
    }
}

bool GearRotate::init_(sead::Heap* heap) {
    _70 = new (heap) xlink2::Handle;
    return true;
}

void GearRotate::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (*mIsTwoWayGear_s) {
        if (auto* body = actor->getMainBody()) {
            sead::Vector3f ang_vel = body->getAngularVelocity();
            const f32 speed = ang_vel.length();
            ang_vel.normalize();
            const auto& mtx = actor->getMtx();
            sead::Vector3f axis = {mtx(0, 2), mtx(1, 2), mtx(2, 2)};
            axis.normalize();
            const f32 v = ang_vel.dot(axis) < 0.0f ? -speed : speed;
            _60.value = v;
            _60.prev_value = v;
        }
        _6c = *mRotateSpeed_m;
        if (*mDgnRotDir_m == 0)
            _6c = -_6c;
        if (*mIsReverse_s)
            _6c = -_6c;
    } else {
        f32 speed = *mRotateSpeed_m;
        if (*mDgnRotDir_m == 0)
            speed = -speed;
        if (*mIsReverse_s)
            speed = -speed;
        _60.value = speed;
        _60.prev_value = speed;
        _6c = speed;
    }

    actor->emitBasicSigOn();
    actor->getMtx().getBase(_50, 0);
    _5c = *mRotateSpeed_m * *mStopCheckSpdRate_s * ksys::VFR::instance()->getDeltaFrame() / 30.0f;
}

void GearRotate::leave_() {
    ksys::act::ai::Action::leave_();
}

void GearRotate::loadParams_() {
    getStaticParam(&mStopCheckSpdRate_s, "StopCheckSpdRate");
    getStaticParam(&mCheckSpdIdlingRate_s, "CheckSpdIdlingRate");
    getStaticParam(&mIsReverse_s, "IsReverse");
    getStaticParam(&mIsTwoWayGear_s, "IsTwoWayGear");
    getMapUnitParam(&mDgnRotDir_m, "DgnRotDir");
    getMapUnitParam(&mRotateSpeed_m, "RotateSpeed");
}

bool GearRotate::handleMessage_(const ksys::Message& message) {
    if (message.getType() == 0x3000003)
        mActor->emitBasicSigOff();
    return false;
}

void GearRotate::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
