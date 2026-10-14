// acc::Camera TU (0x7100799f60-0x710079a8e4): after the Camera TU's RTTI functions, so the accessors
// call the Camera member functions out of line.
#include "Game/Actor/actCamera.h"

namespace ksys::act::acc {

inline uking::act::Camera* Camera::getCamera() const {
    if (!mProc)
        return nullptr;
    return sead::DynamicCast<uking::act::Camera>(sead::DynamicCast<Actor>(mProc));
}

bool Camera::sub_7100799F60() const {
    auto* camera = getCamera();
    if (!camera)
        return false;
    return camera->sub_710079614C();
}

bool Camera::sub_710079A05C() const {
    auto* camera = getCamera();
    if (!camera)
        return false;
    return camera->sub_7100796164();
}

bool Camera::sub_710079A158() const {
    auto* camera = getCamera();
    if (!camera)
        return false;
    return camera->sub_7100794FD0();
}

void Camera::requestCameraPack(const uking::act::Unk_7100791b1c& request) const {
    debugLog(1, "requestCameraPack");
    if (auto* camera = getCamera())
        camera->requestCameraPack(request);
}

void Camera::setSunazarashiTurnParam(const f32& value) const {
    debugLog(1, "setSunazarashiTurnParam");
    if (auto* camera = getCamera())
        camera->setSunazarashiTurnParam(value);
}

void Camera::setWaterRemainsData(const sead::Matrix34f& mtx, const sead::Vector3f& pos) const {
    debugLog(1, "setWaterRemainsData");
    if (auto* camera = getCamera())
        camera->setWaterRemainsData(mtx, pos);
}

f32 Camera::getPlayerAlphaRate() const {
    debugLog(4, "getPlayerAlphaRate");
    auto* camera = getCamera();
    if (!camera)
        return 1.0f;
    return camera->_13f4;
}

}  // namespace ksys::act::acc
