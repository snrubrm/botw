#include "Game/AI/Action/actionCameraVibrate.h"
#include <xlink2/xlink2Event.h>
#include <xlink2/xlink2HandleSLink.h>
#include "Game/AI/aiXlinkHandle.h"
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
    ksys::act::ai::Action::calc_();
}

void CameraVibrate::m32() {}

bool CameraVibrate::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x2000001)
        _64 = *static_cast<const int*>(message->getUserData());
    return true;
}

}  // namespace uking::action
