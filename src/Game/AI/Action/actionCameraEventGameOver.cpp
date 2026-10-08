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

// NON_MATCHING: regalloc only — the original assigns the first two lerp products to s1/s16
// (reusing the dead dx register, then a fresh one) where ours uses s16/s3. Calls, branch structure,
// constants, stack layout and vector forms identical.
void CameraEventGameOver::m44() {
    auto* camera = getCamera();
    if (!camera)
        return;

    act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    auto* player = sub_7100926A14();
    if (!player)
        return;

    _60.sub_710079C408();
    const f32 f8 = 1.0f - _60._18;
    if (_60._18 >= 1.0f)
        setFinished();
    polar._4 = angleStuff(sub_7100924CAC(*mLat_s) + f8 * _4c);
    polar._0 = sub_7100924CAC(*mRadius_s) + f8 * _50;
    const f32 y = *mOffsetY_s + f8 * _54;
    sead::Vector3f v = sead::Vector3f::zero;
    sub_7100926154(player, &v);
    v.y = y + v.y;
    const f32 t = sub_7100791E44(0.4f);
    const f32 dx = v.x - camera->_860._0._c.x;
    const f32 dy = v.y - camera->_860._0._c.y;
    const f32 dz = v.z - camera->_860._0._c.z;
    camera->_860._0._c.x += t * dx;
    camera->_860._0._c.y += t * dy;
    camera->_860._0._c.z += t * dz;
    camera->_860._0._0 = camera->_860._0._c + polar.sub_7100923254();
    camera->_860._0._24 = *mFovy_s + f8 * _58;
}

void CameraEventGameOver::m46() {
    getStaticParam(&mLat_s, "Lat");
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mOffsetY_s, "OffsetY");
    getStaticParam(&mFovy_s, "Fovy");
    getStaticParam(&mCount_s, "Count");
}

}  // namespace uking::action
