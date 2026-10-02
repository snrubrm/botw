#include "Game/AI/Action/actionCameraEventSavePoint.h"

namespace uking::action {

CameraEventSavePoint::CameraEventSavePoint(const InitArg& arg) : CameraAction(arg) {}

bool CameraEventSavePoint::oneShot_() {
    const int save_point = *mSavePoint_s;
    _58 = act::sub_710079BE9C(save_point) ? save_point : 0;
    auto* camera = getCamera();
    if (!camera)
        return false;
    camera->x_1(_58);
    return true;
}

void CameraEventSavePoint::m36() {
    getStaticParam(&mSavePoint_s, "SavePoint");
}

}  // namespace uking::action
