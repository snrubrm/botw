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

}  // namespace ksys::act::acc
