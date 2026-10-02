#include "Game/AI/AI/aiCameraEventReturnSavePoint.h"

namespace uking::ai {

CameraEventReturnSavePoint::CameraEventReturnSavePoint(const InitArg& arg) : CameraEvent(arg) {}

void CameraEventReturnSavePoint::m41() {
    auto* child = getCurrentChild();
    if (child == nullptr || child->isFinished() || child->isFailed())
        setFinished();
}

void CameraEventReturnSavePoint::m43() {
    getStaticParam(&_48, "SavePoint");
    getDynamicParam_2(&_50, "ReviseMode");
    getDynamicParam_2(&_58, "Count");
    getDynamicParam_2(&_60, "CollisionInterpolateSkip");
}

}  // namespace uking::ai
