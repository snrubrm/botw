#include "Game/Actor/Action/actionDungeonRotateBase.h"
#include <xlink2/xlink2Event.h>
#include <xlink2/xlink2HandleSLink.h>
#include "Game/Actor/aiXlinkHandle.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actSoundProxy.h"
#include "Game/gameGearMgr.h"
#include "KingSystem/Sound/sndSound.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

DungeonRotateBase::DungeonRotateBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DungeonRotateBase::~DungeonRotateBase() {
    if (_a0) {
        delete _a0;
        _a0 = nullptr;
    }
    if (_a8) {
        delete _a8;
        _a8 = nullptr;
    }
}

bool DungeonRotateBase::init_(sead::Heap* heap) {
    _90 = mActor->getFieldBodyGroup();
    if (!mActor->getMapObjIter().tryGetParamIntByKey(&_98, "FieldBodyGroup"))
        _98 = -1;
    _7c = *mInitDgnPriority_m;
    _84 = _88 = sead::Mathf::deg2rad(*mTiltAngularSpeed_m);
    _a0 = new (heap) xlink2::HandleSLink;
    _a8 = new (heap) xlink2::HandleSLink;
    return true;
}

void DungeonRotateBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DungeonRotateBase::leave_() {
    if (_a0)
        xlink::fade(*_a0, -1);
    if (_a8)
        xlink::fade(*_a8, -1);
}

void DungeonRotateBase::loadParams_() {
    getStaticParam(&mRotateAxisIndex_s, "RotateAxisIndex");
    getMapUnitParam(&mInitDgnPriority_m, "InitDgnPriority");
    getMapUnitParam(&mCameraPattern_m, "CameraPattern");
    getMapUnitParam(&mRemainsPartType_m, "RemainsPartType");
    getMapUnitParam(&mTiltAngularSpeed_m, "TiltAngularSpeed");
    getMapUnitParam(&mInitDgnRotRad_m, "InitDgnRotRad");
    getMapUnitParam(&mCameraPower_m, "CameraPower");
    getMapUnitParam(&mCameraRange_m, "CameraRange");
    getMapUnitParam(&mVelocityControlRate_m, "VelocityControlRate");
    getMapUnitParam(&mAngleVelocityControlAccelDeg_m, "AngleVelocityControlAccelDeg");
}

ksys::map::Object* DungeonRotateBase::sub_71000FC4EC() {
    if (!mActor)
        return nullptr;
    auto* object = mActor->getMapObject();
    if (!object || !object->getLinkData())
        return nullptr;
    for (auto* linked : object->getLinkData()->mObjects) {
        if (!linked)
            continue;
        const auto& name = linked->getActorData().mActorName;
        if (name.findIndex("SoundProxy") != -1 && name.findIndex("Fixed") == -1)
            return linked;
    }
    return nullptr;
}

// NON_MATCHING: countdown fade block placement and inlined map-scan registers differ.
void DungeonRotateBase::calc_() {
    if (_b0 > 0 && --_b0 == 0) {
        if (_a0)
            xlink::fade(*_a0, -1);
        if (_a8)
            xlink::fade(*_a8, -1);
    }
    _b5 = false;
    auto* gear = GearMgr::instance();
    if (gear && mActor && (gear->_10a8[gear->_28 ^ 1] & 4)) {
        if (gear->sub_71006690B8(mActor)) {
            _b5 = true;
            return;
        }
        if (_b5)
            return;
    }
    if (auto* proxy = ksys::snd::SoundMgr::instance()->_a0->sub_710105A830(sub_71000FC4EC()))
        proxy->sub_710105A4FC();
    if (auto* proxy = ksys::snd::SoundMgr::instance()->_a0->sub_710105A830(findFixedSoundProxyObject()))
        proxy->sub_710105A4FC();
}

inline ksys::map::Object* DungeonRotateBase::findFixedSoundProxyObject() const {
    if (!mActor)
        return nullptr;
    auto* object = mActor->getMapObject();
    if (!object || !object->getLinkData())
        return nullptr;
    for (auto* linked : object->getLinkData()->mObjects) {
        if (!linked)
            continue;
        const auto& name = linked->getActorData().mActorName;
        if (name.findIndex("SoundProxy") != -1 && name.findIndex("Fixed") != -1)
            return linked;
    }
    return nullptr;
}

void DungeonRotateBase::applyParams() {
    _90 = mActor->getFieldBodyGroup();
    _7c = *mInitDgnPriority_m;
    _88 = sead::Mathf::deg2rad(*mTiltAngularSpeed_m);
}

float DungeonRotateBase::m32() {
    _88 = sead::Mathf::deg2rad(*mTiltAngularSpeed_m);
    return _88;
}

void DungeonRotateBase::m33() {
    auto* actor = mActor;
    f32 speed = _88;
    if (actor->checkVelocityControlSignal())
        speed *= *mVelocityControlRate_m;
    _84 = speed;
}

void DungeonRotateBase::m34(f32 x) {
    _8c = sead::Mathf::abs(x);
}

void DungeonRotateBase::m35() {
    f32 target = _88;
    if (mActor->checkVelocityControlSignal())
        target *= *mVelocityControlRate_m;
    ksys::VFR::chase(&_84, target, _8c);
}

// NON_MATCHING: actor capture and camera argument loads are reordered.
void DungeonRotateBase::sub_71000FD51C() {
    if (_a0)
        xlink::fade(*_a0, -1);
    if (_a8)
        xlink::fade(*_a8, -1);
    auto* object = sub_71000FC4EC();
    sub_71005DDC98(mActor, *mCameraPattern_m, _c4 ? _bc : *mCameraPower_m,
                   _c4 ? _c0 : *mCameraRange_m, _b4 != 0, object);
}

}  // namespace uking::action
