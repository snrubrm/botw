#include "Game/Actor/Action/actionGearRotate.h"
#include <cmath>
#include <xlink2/xlink2Event.h>
#include <xlink2/xlink2HandleSLink.h>
#include "Game/Actor/aiXlinkHandle.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
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
    _70 = new (heap) xlink2::HandleSLink;
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
    if (_70)
        xlink::fade(*_70, -1);
}

void GearRotate::loadParams_() {
    getStaticParam(&mStopCheckSpdRate_s, "StopCheckSpdRate");
    getStaticParam(&mCheckSpdIdlingRate_s, "CheckSpdIdlingRate");
    getStaticParam(&mIsReverse_s, "IsReverse");
    getStaticParam(&mIsTwoWayGear_s, "IsTwoWayGear");
    getMapUnitParam(&mDgnRotDir_m, "DgnRotDir");
    getMapUnitParam(&mRotateSpeed_m, "RotateSpeed");
}

bool GearRotate::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x3000003)
        mActor->emitBasicSigOff();
    return false;
}

// NON_MATCHING: direction loads, registers and signal branch arrangement.
void GearRotate::calc_() {
    auto* actor = mActor;
    _60.chase(_6c, *mRotateSpeed_m * 0.04f);
    _60.updateStats();
    if (auto* body = actor->getMainBody()) {
        sead::Vector3f axis;
        actor->getMtx().getBase(axis, 2);
        axis.normalize();
        axis *= _60.value;
        body->setAngularVelocity(axis);
    }
    if (*mIsTwoWayGear_s) {
        if (!actor->checkLinkBasicSig())
            actor->emitBasicSigOn();
    } else {
        sead::Vector3f direction;
        actor->getMtx().getBase(direction, 0);
        const f32 alignment = direction.dot(_50);
        const f32 threshold = std::cos(_5c);
        _5c = *mRotateSpeed_m * *mStopCheckSpdRate_s * ksys::VFR::instance()->getDeltaFrame() / 30.0f;
        if (actor->checkLinkBasicSig() || alignment >= threshold) {
            const bool signal = actor->checkLinkBasicSig();
            if (alignment >= threshold && signal)
                actor->emitBasicSigOff();
        } else {
            actor->emitBasicSigOn();
        }
    }
    actor->getMtx().getBase(_50, 0);
    if (_70) {
        if (sead::Mathf::abs(_60.value) > 0.0f) {
            if (!_70->isActive())
                ksys::eft::sub_710105DDB8(actor, "Roll", _70);
        } else {
            xlink::fade(*_70, -1);
        }
    }
}

}  // namespace uking::action
