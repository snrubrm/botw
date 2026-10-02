#include "Game/AI/Action/actionCameraEventAnimFlowBase.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

CameraEventAnimFlowBase::CameraEventAnimFlowBase(const InitArg& arg) : CameraEventAnimBase(arg) {}

void CameraEventAnimFlowBase::m47() {
    _17c = 0;
}

void CameraEventAnimFlowBase::m48() {
    ksys::Timer::update(&_17c, 1.0f);
}

float CameraEventAnimFlowBase::m49() {
    return _17c;
}

}  // namespace uking::action
