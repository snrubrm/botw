#include "Game/Actor/AI/aiAppearNearTargetOutOfScrnGnd.h"
#include "Game/Actor/aiUnk_7100D8C538.h"
#include "KingSystem/Camera/CameraMgr.h"

namespace uking::ai {

AppearNearTargetOutOfScrnGnd::AppearNearTargetOutOfScrnGnd(const InitArg& arg)
    : AppearFromTarget(arg) {}

AppearNearTargetOutOfScrnGnd::~AppearNearTargetOutOfScrnGnd() = default;

bool AppearNearTargetOutOfScrnGnd::init_(sead::Heap* heap) {
    return AppearFromTarget::init_(heap);
}

void AppearNearTargetOutOfScrnGnd::enter_(ksys::act::ai::InlineParamPack* params) {
    AppearFromTarget::enter_(params);
}

void AppearNearTargetOutOfScrnGnd::calc_() {
    AppearFromTarget::calc_();
}

void AppearNearTargetOutOfScrnGnd::leave_() {
    AppearFromTarget::leave_();
}

void AppearNearTargetOutOfScrnGnd::loadParams_() {
    AppearFromTarget::loadParams_();
}

void AppearNearTargetOutOfScrnGnd::m34(sead::Vector3f* out) {
    sead::Vector3f dir;
    ksys::sub_7100D8C7FC(&dir);
    dir.y = 0;
    const f32 sq_length = dir.squaredLength();
    if (sq_length <= sead::Mathf::epsilon() && sq_length >= -sead::Mathf::epsilon()) {
        dir = sead::Vector3f::ez;
    } else {
        dir.negate();
        dir.normalize();
    }
    *out = dir;
}

void AppearNearTargetOutOfScrnGnd::m35(sead::Vector3f* out) {
    cam::getCameraPositionMaybe(out);
}

bool AppearNearTargetOutOfScrnGnd::m36(const sead::Vector3f& pos) {
    return !ksys::sub_7100D8C4F8(pos);
}

}  // namespace uking::ai
