#include "KingSystem/Camera/CameraMgr.h"
#include <gfx/seadCamera.h>
#include <gfx/seadViewport.h>
#include "Game/Actor/aiUnk_7100D8C538.h"
#include "KingSystem/Chemical/chmElement.h"

bool sub_7100D8C538(const sead::Vector3f& pos, f32 near_clip, f32 far_clip) {
    auto* camera = ksys::CameraMgr::instance()->getLookAtCamera();
    if (!camera)
        return false;
    return static_cast<ksys::Unk_71024dd110*>(camera)->sub_7100D8B080(pos, near_clip, far_clip);
}

bool visibilityCheckMaybe(const sead::Vector3f& pos, f32 radius) {
    auto* camera = ksys::CameraMgr::instance()->getLookAtCamera();
    if (!camera)
        return false;
    return static_cast<ksys::Unk_71024dd110*>(camera)->sub_7100D8B1F4(pos, radius);
}

bool sub_7100D8C5E8(const sead::Vector3f& pos, f32 radius, f32 near_clip, f32 far_clip) {
    auto* camera = ksys::CameraMgr::instance()->getLookAtCamera();
    if (!camera)
        return false;
    return static_cast<ksys::Unk_71024dd110*>(camera)->sub_7100D8B138(pos, radius, near_clip, far_clip);
}

namespace ksys {

bool sub_7100D8C658(const sead::Vector3f& pos, f32 radius) {
    auto* camera = CameraMgr::instance()->sub_7100D8C4C0();
    if (!camera)
        return false;
    return camera->sub_7100D8B2AC(pos, radius);
}

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

f32 sub_7100D8C888() {
    auto* camera = CameraMgr::instance()->getLookAtCamera();
    if (!camera)
        return 0.0f;
    return static_cast<Unk_71024dd110*>(camera)->_74;
}

f32 sub_7100D8C8BC() {
    auto* camera = CameraMgr::instance()->getLookAtCamera();
    if (!camera)
        return 0.0f;
    return sead::Mathf::rad2deg(static_cast<Unk_71024dd110*>(camera)->_74);
}

}  // namespace ksys

ElementName::ElementName() = default;
