#include "KingSystem/System/CameraMgr.h"
#include <gfx/seadCamera.h>

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
