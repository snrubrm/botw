#include "Game/AI/AI/aiAppearNearTargetOutOfScrnGnd.h"
#include "Game/AI/aiUnk_7100D8C538.h"
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

void AppearNearTargetOutOfScrnGnd::m35(sead::Vector3f* out) {
    cam::getCameraPositionMaybe(out);
}

bool AppearNearTargetOutOfScrnGnd::m36(const sead::Vector3f& pos) {
    return !ksys::sub_7100D8C4F8(pos);
}

}  // namespace uking::ai
