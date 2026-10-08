#include "KingSystem/System/CameraMgr.h"
#include <gfx/seadCamera.h>
#include <gfx/seadViewport.h>

namespace ksys {

SEAD_SINGLETON_DISPOSER_IMPL(CameraMgr)

bool sub_7100D8C6AC(sead::Vector3f* out) {
    auto* camera = CameraMgr::instance()->getLookAtCamera();
    if (!camera) {
        *out = sead::Vector3f::zero;
        return false;
    }
    *out = camera->getPos();
    return true;
}

f32 sub_7100D8C8FC() {
    const auto* viewport = CameraMgr::instance()->sub_7100D8C4C8();
    if (!viewport)
        return 1.0f;
    return viewport->getSizeX() / viewport->getSizeY();
}

bool sub_7100D8C7FC(sead::Vector3f* out) {
    if (!out)
        return false;
    auto* camera = CameraMgr::instance()->getLookAtCamera();
    if (!camera) {
        *out = sead::Vector3f::zero;
        return false;
    }
    camera->getLookVectorByMatrix(out);
    out->negate();
    return true;
}

}  // namespace ksys
