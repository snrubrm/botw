#include "Game/AI/Action/actionCameraEventAnimBase.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

CameraEventAnimBase::CameraEventAnimBase(const InitArg& arg) : CameraEvent(arg) {}

bool CameraEventAnimBase::handleMessage_(const ksys::Message* message) {
    if (message) {
        if (message->getType() != 0x8800007)
            return false;
        sub_7100757A78();
        if (_90 == 2)
            sub_7100757C24();
    }
    return true;
}

// NON_MATCHING: matrix rotation copying and accessor lifetime scheduling differ.
void CameraEventAnimBase::sub_7100757C24() {
    if (!_50.hasProc())
        return;
    sead::Matrix34f transform;
    sub_7100925AB8(_50, &transform);
    if (ksys::util::sub_71011F10F4(transform)) {
        ksys::act::ActorConstDataAccess target;
        ksys::act::acquireActor(&_50, &target);
        return;
    }
    if (!(_17a & 1)) {
        _60 = transform;
    } else {
        if (m58() != 2) {
            for (s32 axis = 0; axis < 3; ++axis)
                _60.setBase(axis, transform.getBase(axis));
        }
        if (m56() != 2)
            _60.setTranslation(transform.getTranslation());
    }
    _17a |= 1;
}

// NON_MATCHING: the no-target sentinel compare uses an unsigned byte instead of sign extension.
void CameraEventAnimBase::sub_71007583CC() {
    const u8 type = m52();
    if (type != 1) {
        if (type == u8(-1)) {
            _90 = 1;
        } else if (auto* actor = getActor()) {
            if (m52() != u8(-1)) {
                ksys::act::ActorConstDataAccess access(actor);
                sendMessage(*access.getMessageTransceiverId(), ksys::MessageType(0x8800007), nullptr);
            }
        }
        return;
    }
    sub_7100757A78();
    sub_7100757C24();
}

void CameraEventAnimBase::sub_7100758F80(const ksys::act::ActorConstDataAccess* access) {
    if (access && access->hasProc()) {
        access->linkAcquire(&_50);
        _90 = 2;
    }
}

void CameraEventAnimBase::sub_7100758FC0(const ksys::map::Object* object) {
    if (!object)
        return;
    _90 = 3;
    const sead::Vector3f rotate = object->getRotate();
    const sead::Vector3f translate = object->getTranslate();
    _60.makeRT(rotate, translate);
    _17a |= 1;
}

// NON_MATCHING: block layout (the original tests m51 first and evaluates the type compares late, and selects the offset
// words per branch; ours hoists the compares and selects the offset addresses).
void CameraEventAnimBase::sub_710075863C() {
    if (_17a & 2)
        return;

    auto* camera = getCamera();
    if (!camera)
        return;

    const u8 type = m56();
    if (!m51() && type != 3 && (_17a & 1)) {
        sead::Vector3f offset;
        if (type == 0) {
            const sead::Matrix34f* mtx = camera->m159();
            offset.set(mtx->m[0][3], mtx->m[1][3], mtx->m[2][3]);
        } else {
            offset.set(_60.m[0][3], _60.m[1][3], _60.m[2][3]);
        }
        _94.set(camera->_860._0._c.x - offset.x, camera->_860._0._c.y - offset.y,
                camera->_860._0._c.z - offset.z);
    } else {
        _94 = camera->_860._0._c;
    }
    _17a |= 2;
}

void CameraEventAnimBase::m45() {
    if (auto* camera = getCamera())
        camera->sub_7100799920();
}

void CameraEventAnimBase::m46() {
    getDynamicParam(&mSceneName_d, "SceneName");
    getDynamicParam(&mCameraName_d, "CameraName");
    getDynamicParam_2(&mStartFrame_d, "StartFrame");
    getDynamicParam_2(&mEndFrame_d, "EndFrame");
    getDynamicParam_2(&mDOFStartFrame_d, "DOFStartFrame");
    getDynamicParam_2(&mFocalLength_d, "FocalLength");
    getDynamicParam_2(&mAperture_d, "Aperture");
    getDynamicParam_2(&mDOFBlurStart_d, "DOFBlurStart");
    getDynamicParam_2(&mDOFEndFrame_d, "DOFEndFrame");
    getDynamicParam_2(&mFocalLengthEnd_d, "FocalLengthEnd");
    getDynamicParam_2(&mApertureEnd_d, "ApertureEnd");
    getDynamicParam_2(&mDOFBlurEnd_d, "DOFBlurEnd");
    getDynamicParam_2(&mOverwriteAtDist_d, "OverwriteAtDist");
    getDynamicParam_2(&mInterpolateCount_d, "InterpolateCount");
    getDynamicParam_2(&mDOFUse_d, "DOFUse");
    getDynamicParam_2(&mOverwriteAt_d, "OverwriteAt");
    getDynamicParam_2(&mBgCheck_d, "BgCheck");
}

void CameraEventAnimBase::m47() {}

void CameraEventAnimBase::m48() {}

float CameraEventAnimBase::m49() {
    return 0.0f;
}

void CameraEventAnimBase::m50(sead::BufferedSafeString* out) {
    out->copy(mSceneName_d);
}

u8 CameraEventAnimBase::m52() {
    return -1;
}

void CameraEventAnimBase::m53() {}

const sead::SafeString& CameraEventAnimBase::m54() {
    return sead::SafeString::cEmptyString;
}

const sead::SafeString& CameraEventAnimBase::m55() {
    return sead::SafeString::cEmptyString;
}

u8 CameraEventAnimBase::m56() {
    return 3;
}

void CameraEventAnimBase::m57() {}

u8 CameraEventAnimBase::m58() {
    return 3;
}

void CameraEventAnimBase::m59() {}

bool CameraEventAnimBase::m60() {
    return false;
}

}  // namespace uking::action
