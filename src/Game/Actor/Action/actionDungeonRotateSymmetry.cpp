#include "Game/Actor/Action/actionDungeonRotateSymmetry.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include <xlink2/xlink2Event.h>
#include <xlink2/xlink2HandleSLink.h>
#include "Game/Actor/aiXlinkHandle.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actSoundProxy.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physStaticCompoundMgr.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

DungeonRotateSymmetry::DungeonRotateSymmetry(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DungeonRotateSymmetry::~DungeonRotateSymmetry() {
    if (_88) {
        delete _88;
        _88 = nullptr;
    }
}

bool DungeonRotateSymmetry::init_(sead::Heap* heap) {
    _88 = new (heap) xlink2::HandleSLink;
    return true;
}

// NON_MATCHING: home-axis component stores and finished-state comparison are reordered.
void DungeonRotateSymmetry::enter_(ksys::act::ai::InlineParamPack* params) {
    _6c = 0;
    _70 = 0;
    const f32 initial_rotation = *mInitDgnRotRad_m;
    _85 = false;
    _86 = false;
    _84 = initial_rotation < 0 ? 3 : initial_rotation > 0 ? 1 : 0;

    auto* actor = mActor;
    _78 = actor->getFieldBodyGroup();
    if (!actor->getMapObjIter().tryGetParamIntByKey(&_80, "FieldBodyGroup"))
        _80 = -1;
    _74 = sead::Mathf::deg2rad(*mTiltAngularSpeed_m);
    actor->getHomeMtxRaw().getBase(_60, 1);
    if (_70 == _6c)
        _86 = true;
    sub_71005DDE8C(actor, &_60, *mRemainsPartType_m);
    _90 = 0;

    if (auto* proxy = ksys::snd::SoundMgr::instance()->_a0->sub_710105A830(findSoundProxyObject()))
        proxy->_8b8 = true;
}

inline ksys::map::Object* DungeonRotateSymmetry::findSoundProxyObject() const {
    if (mActor && mActor->getMapObject() && mActor->getMapObject()->getLinkData()) {
        for (auto* object : mActor->getMapObject()->getLinkData()->mObjects) {
            if (object && object->getActorData().mActorName.findIndex("SoundProxy") != -1)
                return object;
        }
    }
    return nullptr;
}

void DungeonRotateSymmetry::leave_() {
    if (_88)
        xlink::fade(*_88, -1);
}

void DungeonRotateSymmetry::loadParams_() {
    getMapUnitParam(&mInitDgnPriority_m, "InitDgnPriority");
    getMapUnitParam(&mCameraPattern_m, "CameraPattern");
    getMapUnitParam(&mRemainsPartType_m, "RemainsPartType");
    getMapUnitParam(&mTiltAngle_m, "TiltAngle");
    getMapUnitParam(&mTiltAngularSpeed_m, "TiltAngularSpeed");
    getMapUnitParam(&mInitDgnRotRad_m, "InitDgnRotRad");
    getMapUnitParam(&mCameraPower_m, "CameraPower");
    getMapUnitParam(&mCameraRange_m, "CameraRange");
}

// NON_MATCHING: countdown block placement, switch loads and matrix composition scheduling differ.
void DungeonRotateSymmetry::calc_() {
    if (_90 > 0 && --_90 == 0 && _88)
        xlink::fade(*_88, -1);

    auto* actor = mActor;
    const bool signal = actor->checkBasicSig();
    if (signal != _85) {
        _85 = signal;
        ++_84;
        switch (_84) {
        case 0:
        case 2:
            _6c = 0;
            break;
        case 1:
            _6c = sead::Mathf::deg2rad(*mTiltAngle_m);
            break;
        case 3:
            _6c = -sead::Mathf::deg2rad(*mTiltAngle_m);
            break;
        case 4:
            _84 = 0;
            _6c = 0;
            break;
        }
        _6c += *mInitDgnRotRad_m * -sead::Mathf::deg2rad(1.0f);
    }

    const bool finished = ksys::VFR::chase(&_70, _6c, _74);
    auto* proxy = ksys::snd::SoundMgr::instance()->_a0->sub_710105A830(findSoundProxyObject());
    if (_78 && !_86) {
        sead::Matrix34f rotation;
        rotation.makeR(_60 * _70);
        const sead::Vector3f home_position = actor->getHomeMtxRaw().getTranslation();
        sead::Matrix34f inverse_home;
        inverse_home.makeT(-home_position);
        sead::Matrix34f transform;
        transform.setMul(rotation, inverse_home);
        sead::Matrix34f translation;
        translation.makeT(home_position);
        transform.setMul(translation, transform);
        if (auto* manager = ksys::phys::System::instance()->getStaticCompoundMgr())
            manager->setExtraTransform(_78, transform, *mInitDgnPriority_m);
        if (auto* manager = ksys::phys::HavokAI::instance()->_48) {
            if (_80 >= 0)
                manager->sub_7100F8AA78(_80, transform);
        }
        if (proxy) {
            const sead::Vector3f position = actor->getMtx().getTranslation();
            const sead::Vector3f angles = transform.getRotation();
            proxy->sub_710105A0D8(angles, position);
        }
        if (finished) {
            if (!_86 && finished) {
                if (_88)
                    xlink::fade(*_88, -1);
                sub_71005DDC98(actor, *mCameraPattern_m, *mCameraPower_m, *mCameraRange_m,
                               false, findSoundProxyObject());
            }
        } else {
            if (_90 < 1)
                sub_7100100A6C();
            _90 = 2;
        }
    }
    _86 = finished;
    sub_71005DDE8C(actor, &_60, *mRemainsPartType_m);
    if (proxy)
        proxy->sub_710105A4FC();
}

void DungeonRotateSymmetry::sub_7100100A6C() {
    if (!_88)
        return;
    if (auto* proxy = ksys::snd::SoundMgr::instance()->_a0->sub_710105A830(findSoundProxyObject())) {
        xlink2::HandleSLink handle;
        proxy->sub_710105A10C("Start", &handle);
        if (!_88->isActive())
            proxy->sub_710105A10C("Rotate", _88);
    } else {
        xlink2::HandleSLink handle;
        ksys::eft::sub_710105DDB8(mActor, "Start", &handle);
        if (!_88->isActive())
            ksys::eft::sub_710105DDB8(mActor, "Rotate", _88);
    }
}

void DungeonRotateSymmetry::applyParams() {
    _78 = mActor->getFieldBodyGroup();
    _74 = sead::Mathf::deg2rad(*mTiltAngularSpeed_m);
}

}  // namespace uking::action
