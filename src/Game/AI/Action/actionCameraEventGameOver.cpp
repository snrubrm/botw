#include "Game/AI/Action/actionCameraEventGameOver.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actCameraUtil.h"

namespace uking::action {

CameraEventGameOver::CameraEventGameOver(const InitArg& arg) : CameraEvent(arg) {}

CameraEventGameOver::~CameraEventGameOver() = default;

void CameraEventGameOver::m43() {
    auto* camera = getCamera();
    if (!camera)
        return;

    const auto& state = camera->_860._0;
    act::Unk_7100922700 polar(state._0 - state._c);
    const f32 lat = sub_7100924CAC(*mLat_s);
    _4c = angleStuff(polar._4 - lat);
    _50 = polar._0 - sub_7100924D40(*mRadius_s);
    _54 = -*mOffsetY_s;
    _58 = state._24 - *mFovy_s;
    _60.sub_710079C384(sead::Mathf::clampMin(*mCount_s, 0.0f), 0.0f);
}

void CameraEventGameOver::m46() {
    getStaticParam(&mLat_s, "Lat");
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mOffsetY_s, "OffsetY");
    getStaticParam(&mFovy_s, "Fovy");
    getStaticParam(&mCount_s, "Count");
}

}  // namespace uking::action
