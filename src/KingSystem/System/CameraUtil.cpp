#include "KingSystem/System/CameraMgr.h"
#include <gfx/seadCamera.h>
#include <gfx/seadViewport.h>

namespace ksys {

bool sub_7100D8C4F8(const sead::Vector3f& pos) {
    auto* camera = CameraMgr::instance()->getLookAtCamera();
    if (!camera)
        return false;
    // Both selector registration paths use this native LookAtCamera subtype.
    return static_cast<Unk_71024dd110*>(camera)->sub_7100D8AFCC(pos);
}

bool sub_7100D8C6AC(sead::Vector3f* out) {
    auto* camera = CameraMgr::instance()->getLookAtCamera();
    if (!camera) {
        *out = sead::Vector3f::zero;
        return false;
    }
    *out = camera->getPos();
    return true;
}

bool sub_7100D8C71C(sead::Vector3f* out) {
    auto* camera = CameraMgr::instance()->getLookAtCamera();
    if (!camera) {
        *out = sead::Vector3f::zero;
        return false;
    }
    *out = camera->getAt();
    return true;
}

bool sub_7100D8C78C(sead::Vector3f* out) {
    auto* camera = CameraMgr::instance()->getLookAtCamera();
    if (!camera) {
        *out = sead::Vector3f::zero;
        return false;
    }
    *out = camera->getUp();
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
