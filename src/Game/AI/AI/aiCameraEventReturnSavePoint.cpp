#include "Game/AI/AI/aiCameraEventReturnSavePoint.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

CameraEventReturnSavePoint::CameraEventReturnSavePoint(const InitArg& arg) : CameraEvent(arg) {}

void CameraEventReturnSavePoint::m40(ksys::act::ai::InlineParamPack* params) {
    auto* camera = getCamera();
    if (!camera || !camera->_860._72c._4.isValid()) {
        changeChild("エラー");
        return;
    }
    switch (camera->_860._72c._4._38.load()) {
    case 0: {
        ksys::act::ai::InlineParamPack pack;
        pack.addFloat(*_58, "Count", -1);
        pack.addFloat(0.1f, "Cushion", -1);
        pack.addBool(false, "StartCalcOnly", -1);
        pack.addBool(true, "CollisionInterpolateSkip", -1);
        pack.addInt(*_50, "ReviseModeRunning", -1);
        pack.addInt(*_50, "ReviseModeEnd", -1);
        pack.addFloat(0.0f, "LatShiftRange", -1);
        pack.addFloat(0.0f, "LngShiftRange", -1);
        pack.addInt(-1, "ActorIgnoringCollision", -1);
        changeChild("デフォルト", &pack);
        break;
    }
    case 1: {
        ksys::act::ai::InlineParamPack pack;
        pack.addInt(_68, "SavePoint", -1);
        pack.addFloat(*_58, "Count", -1);
        changeChild("会話", &pack);
        break;
    }
    default:
        changeChild("エラー");
        break;
    }
}

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
