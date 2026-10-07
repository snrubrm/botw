#include "Game/AI/Action/actionCameraEventAnimFlowForMapTower.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

CameraEventAnimFlowForMapTower::CameraEventAnimFlowForMapTower(const InitArg& arg)
    : CameraEventAnimFlow(arg) {}

void CameraEventAnimFlowForMapTower::m50(sead::BufferedSafeString* out) {
    *out = sead::SafeString("");
    if (auto* camera = getCameraActor()) {
        sead::Vector3f position;
        camera->_860._270.getTranslation(position);
        sead::FixedSafeString<16> name;
        ui::sub_7100A9F55C(&name, &position, 10.0f);
        out->appendWithFormat("%s-%s", mSceneName_d.cstr(), name.cstr());
    }
}

}  // namespace uking::action
