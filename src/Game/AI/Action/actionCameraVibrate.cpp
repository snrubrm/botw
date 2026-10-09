#include "Game/AI/Action/actionCameraVibrate.h"
#include <xlink2/xlink2Event.h>
#include <xlink2/xlink2HandleSLink.h>
#include "Game/AI/aiXlinkHandle.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actSoundProxy.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/Sound/sndMgr.h"
#include "KingSystem/System/Vibration.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace uking::action {

namespace {
ksys::util::InitConstants sInitConstants;
ksys::util::InitTimeInfo sInitTimeInfo;
}  // namespace

CameraVibrate::CameraVibrate(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CameraVibrate::~CameraVibrate() {
    if (_68) {
        delete _68;
        _68 = nullptr;
    }
}

bool CameraVibrate::init_(sead::Heap* heap) {
    _68 = new (heap) xlink2::HandleSLink;
    return true;
}

void CameraVibrate::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CameraVibrate::leave_() {
    if (_68->getEvent() && _68->getEvent()->getCreateId() == u32(_68->getCreateId()))
        xlink::fade(*_68, -1);
}

void CameraVibrate::loadParams_() {
    getMapUnitParam(&mCameraPattern_m, "CameraPattern");
    getMapUnitParam(&mCameraPower_m, "CameraPower");
    getMapUnitParam(&mCameraRange_m, "CameraRange");
    getStaticParam(&mIsSound_s, "IsSound");
    getStaticParam(&mStartSoundName_s, "StartSoundName");
    getStaticParam(&mLoopSoundName_s, "LoopSoundName");
}

void CameraVibrate::calc_() {
    const bool active = mActor->checkBasicSig();
    if (_60 == active)
        return;
    if (active) {
        auto* actor = mActor;
        ksys::Vibration::Unk2 request;
        request._20 = *mCameraPattern_m;
        request._18 = *mCameraPower_m;
        request._1c = *mCameraRange_m;
        sead::Vector3f home_pos;
        actor->getHomePos(&home_pos);
        request._0 = home_pos;
        request._10 = &actor->getMessageTransceiver();
        request._25 = 1;
        ksys::Vibration::instance()->sub_71010BB428(request);
        sub_7100051124();
    } else {
        if (_64 >= 0)
            ksys::Vibration::instance()->sub_71010BB810(_64);
        sub_71000512C0();
    }
    _60 = active;
}

// NON_MATCHING: object traversal, string and handle lifetime scheduling differ.
void CameraVibrate::sub_7100051124() {
    if (!*mIsSound_s)
        return;
    auto* manager = ksys::snd::SoundMgr::instance()->_a0;
    ksys::map::Object* proxy_object = nullptr;
    if (mActor) {
        auto* object = mActor->getMapObject();
        if (object && object->getLinkData()) {
            for (auto* linked : object->getLinkData()->mObjects) {
                if (!linked)
                    continue;
                const auto& name = linked->getActorData().mActorName;
                if (name.findIndex("SoundProxy") != -1 && name.findIndex("Fixed") == -1) {
                    proxy_object = linked;
                    break;
                }
            }
        }
    }
    if (auto* proxy = manager->sub_710105A830(proxy_object)) {
        xlink2::HandleSLink start_handle;
        const sead::SafeString start_name(mStartSoundName_s.cstr());
        proxy->sub_710105A10C(start_name, &start_handle);
        const sead::SafeString loop_name(mLoopSoundName_s.cstr());
        proxy->sub_710105A10C(loop_name, _68);
    }
}

// NON_MATCHING: object traversal, string and handle lifetime scheduling differ.
void CameraVibrate::sub_71000512C0() {
    if (!*mIsSound_s)
        return;
    auto* manager = ksys::snd::SoundMgr::instance()->_a0;
    ksys::map::Object* proxy_object = nullptr;
    if (mActor) {
        auto* object = mActor->getMapObject();
        if (object && object->getLinkData()) {
            for (auto* linked : object->getLinkData()->mObjects) {
                if (!linked)
                    continue;
                const auto& name = linked->getActorData().mActorName;
                if (name.findIndex("SoundProxy") != -1 && name.findIndex("Fixed") == -1) {
                    proxy_object = linked;
                    break;
                }
            }
        }
    }
    manager->sub_710105A830(proxy_object);
    if (_68->getEvent() && _68->getEvent()->getCreateId() == u32(_68->getCreateId()))
        xlink::fade(*_68, -1);
}

void CameraVibrate::m32() {}

bool CameraVibrate::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x2000001)
        _64 = *static_cast<const int*>(message->getUserData());
    return true;
}

}  // namespace uking::action
