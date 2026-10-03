#include "Game/AI/AI/aiAppearNearTargetOutOfScrnGnd.h"
#include "KingSystem/System/CameraMgr.h"

namespace uking::ai {

AppearNearTargetOutOfScrnGnd::AppearNearTargetOutOfScrnGnd(const InitArg& arg)
    : AppearNearTarget(arg) {}

AppearNearTargetOutOfScrnGnd::~AppearNearTargetOutOfScrnGnd() = default;

bool AppearNearTargetOutOfScrnGnd::init_(sead::Heap* heap) {
    return AppearNearTarget::init_(heap);
}

void AppearNearTargetOutOfScrnGnd::enter_(ksys::act::ai::InlineParamPack* params) {
    AppearNearTarget::enter_(params);
}

void AppearNearTargetOutOfScrnGnd::calc_() {
    AppearNearTarget::calc_();
}

void AppearNearTargetOutOfScrnGnd::leave_() {
    AppearNearTarget::leave_();
}

void AppearNearTargetOutOfScrnGnd::loadParams_() {
    AppearNearTarget::loadParams_();
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
    ksys::sub_7100D8C6AC(out);
}

bool AppearNearTargetOutOfScrnGnd::m36(const sead::Vector3f& pos) {
    return !ksys::sub_7100D8C4F8(pos);
}

}  // namespace uking::ai
