#include "Game/Actor/Action/actionDungeonMove.h"
#include <xlink2/xlink2Event.h>
#include <xlink2/xlink2HandleSLink.h>
#include "Game/Actor/aiXlinkHandle.h"
#include "Game/Actor/actSoundProxy.h"
#include "KingSystem/Physics/System/physStaticCompoundMgr.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/System/VFR.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"

namespace uking::action {

DungeonMove::DungeonMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DungeonMove::~DungeonMove() {
    if (_90) {
        delete _90;
        _90 = nullptr;
    }
}

bool DungeonMove::init_(sead::Heap* heap) {
    _80 = mActor->getFieldBodyGroup();
    if (!mActor->getMapObjIter().tryGetParamIntByKey(&_88, "FieldBodyGroup"))
        _88 = -1;
    _78 = *mInitDgnPriority_m;
    _90 = new (heap) xlink2::HandleSLink;
    return true;
}

// NON_MATCHING: home matrix and axis values use stack storage rather than preserved scalar registers.
void DungeonMove::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* manager = ksys::phys::System::instance()->getStaticCompoundMgr();
    _74 = *mMoveSpeed_m;
    const sead::Matrix34f home = mActor->getHomeMtxRaw();
    if (manager) {
        sead::Matrix34f transformed;
        transformed.setMul(manager->getExtraTransform(_80, _78), home);
        transformed.getTranslation(_58);
    }
    _64 = home.getTranslation() + home.getBase(1) * *mDynMoveDis_d;
    _70 = 0;
    mFlags.set(Flag::Changeable);
    _8c = false;
    if (auto* proxy = ksys::snd::SoundMgr::instance()->_a0->sub_710105A830(sub_71000F9C9C()))
        proxy->_8b8 = true;
}

void DungeonMove::leave_() {
    if (_90->getEvent() && _90->getEvent()->getCreateId() == u32(_90->getCreateId()))
        xlink::fade(*_90, -1);
}

void DungeonMove::loadParams_() {
    getStaticParam(&mAccel_s, "Accel");
    getDynamicParam(&mDynMoveDis_d, "DynMoveDis");
    getMapUnitParam(&mInitDgnPriority_m, "InitDgnPriority");
    getMapUnitParam(&mCameraPattern_m, "CameraPattern");
    getMapUnitParam(&mMoveSpeed_m, "MoveSpeed");
    getMapUnitParam(&mCameraPower_m, "CameraPower");
    getMapUnitParam(&mCameraRange_m, "CameraRange");
}

ksys::map::Object* DungeonMove::sub_71000F9C9C() {
    if (!mActor)
        return nullptr;
    auto* object = mActor->getMapObject();
    if (!object || !object->getLinkData())
        return nullptr;
    for (auto* linked : object->getLinkData()->mObjects) {
        if (linked && linked->getActorData().mActorName.findIndex("SoundProxy") != -1)
            return linked;
    }
    return nullptr;
}

// NON_MATCHING: vector chase copies and matrix composition scheduling differ.
void DungeonMove::calc_() {
    auto* actor = mActor;
    const f32 acceleration = *mAccel_s;
    ksys::VFR::chase(&_70, _74, acceleration);
    const bool finished = ksys::VFR::chaseVec(&_58, _64, _70);
    auto* sound_object = sub_71000F9C9C();
    auto* proxy = ksys::snd::SoundMgr::instance()->_a0->sub_710105A830(sound_object);
    bool moving = false;
    if (_80 && !_8c) {
        const sead::Vector3f home_position = actor->getHomeMtxRaw().getTranslation();
        sead::Matrix34f rotation;
        rotation.makeR(sead::Vector3f::zero);
        sead::Matrix34f inverse_home;
        inverse_home.makeT(-home_position);
        sead::Matrix34f transform;
        transform.setMul(rotation, inverse_home);
        sead::Matrix34f translation;
        translation.makeT(_58);
        transform.setMul(translation, transform);
        if (auto* manager = ksys::phys::System::instance()->getStaticCompoundMgr())
            manager->setExtraTransform(_80, transform, _78);
        if (auto* manager = ksys::phys::HavokAI::instance()->_48) {
            if (_88 >= 0)
                manager->sub_7100F8AA78(_88, transform);
        }
        if (proxy)
            transform.getTranslation(proxy->_848);
        moving = true;
        if (!_8c && finished) {
            if (_90->isActive())
                xlink::fade(*_90, -1);
            sub_71005DDC98(actor, *mCameraPattern_m, *mCameraPower_m, *mCameraRange_m,
                           false, sound_object);
            setFinished();
        }
    }
    _8c = finished;
    const bool active = _90->isActive();
    if (moving) {
        if (!active)
            sub_71000FA43C();
    } else if (active) {
        xlink::fade(*_90, -1);
    }
    if (proxy)
        proxy->sub_710105A4FC();
}

void DungeonMove::sub_71000FA43C() {
    if (auto* proxy = ksys::snd::SoundMgr::instance()->_a0->sub_710105A830(sub_71000F9C9C())) {
        xlink2::HandleSLink handle;
        proxy->sub_710105A10C("Start", &handle);
        proxy->sub_710105A10C("Move", _90);
    } else {
        xlink2::HandleSLink handle;
        ksys::eft::sub_710105DDB8(mActor, "Start", &handle);
        ksys::eft::sub_710105DDB8(mActor, "Move", _90);
    }
}

void DungeonMove::applyParams() {
    _80 = mActor->getFieldBodyGroup();
    _74 = *mMoveSpeed_m;
    _78 = *mInitDgnPriority_m;
}

}  // namespace uking::action
