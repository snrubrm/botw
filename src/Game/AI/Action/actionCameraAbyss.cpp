#include "Game/AI/Action/actionCameraAbyss.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actCameraUtil.h"

namespace uking::action {

CameraAbyss::CameraAbyss(const InitArg& arg) : CameraAction(arg) {}

void CameraAbyss::m33() {
    _70 = sub_7100924D40(*mRadiusMin_s);
    _74 = sub_7100924D50(*mFovy_s);

    auto* camera = getCamera();
    if (!camera)
        return;

    sead::Vector3f at = sead::Vector3f::zero;
    camera->_860._0.sub_7100921A90(&at);
    const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    sead::Vector3f base = camera->_860._270.getTranslation();
    base.y = at.y;
    act::Unk_7100922700 target = polar;
    target._0 = sead::Mathf::clampMin(sub_71009226EC(target._4) * target._0, _70);
    target._4 = angleStuff(0.0f);
    _4c = base + target.sub_7100923254();
    _58 = target._0;
    setFinished();
}

// NON_MATCHING: the original keeps the z subtraction of the else branch inside the branch
void CameraAbyss::m34() {
    auto* camera = getCamera();
    if (!camera)
        return;

    auto& data = camera->_860;
    data._0 = data._38 = data._70 = data._a8 = data._e0;

    const sead::Vector3f trans = data._270.getTranslation();
    const act::Unk_7100922700 cur(data._0._c - data._0._0);
    act::Unk_7100922700 polar = cur;

    sead::Vector3f at = sead::Vector3f::zero;
    data._0.sub_7100921A90(&at);
    sead::Vector3f base = trans;
    base.y = at.y;
    const f32 dy = trans.y - at.y;
    const f32 rate = sub_710092523C(sub_71009251C4(getCameraActor()), 0.2f);
    if (dy > -3.0f)
        at += (_4c - at) * rate;
    else
        at += (base - at) * rate;

    f32 elevation;
    const f32 dist = (at - base).length();
    if (dist > 0.0f)
        elevation = sead::Mathf::rad2deg(std::atan2(trans.y - data._0._0.y, dist));
    else
        elevation = -89.9f;
    elevation = sub_7100924CAC(elevation);

    if (angleStuff(polar._4) > angleStuff(elevation)) {
        const f32 t = sub_7100791E44(0.6f);
        polar._4 = angleStuff(
            angleStuff(t * angleStuff(angleStuff(elevation) - polar._4)) + polar._4);
    }

    sead::Vector3f dir = -polar.sub_7100923254();
    dir.normalize();
    data._0._0 = at + dir * data._0._30;
    data._0._c = data._0._0 + polar.sub_7100923254();

    data._0._24 += sub_710092523C(sub_71009251C4(getCameraActor()), 0.1f) * (_74 - data._0._24);
    camera->sub_71007953C8();
    data._818 |= 0xc;
}

void CameraAbyss::m36() {
    getStaticParam(&mRadiusMin_s, "RadiusMin");
    getStaticParam(&mFovy_s, "Fovy");
}

}  // namespace uking::action
