#include "Game/AI/Action/actionCameraEventLookBase.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/System/Timer.h"

namespace uking::action {

CameraEventLookBase::CameraEventLookBase(const InitArg& arg) : CameraEvent(arg) {}

// NON_MATCHING: typed state copying and matrix/vector initialization scheduling differ.
void CameraEventLookBase::m43() {
    auto* camera = getCamera();
    if (!camera)
        return;
    _84 = 0.0f;
    const f32 min_latitude = sub_7100924CAC(*mLatMin_d);
    const f32 max_latitude = sub_7100924CAC(*mLatMax_d);
    sub_7100924CDC(min_latitude, max_latitude, &_90, &_94);
    _119 = u32(*mLatMode_d) < 2 ? *mLatMode_d : 0;
    _11a = u32(*mReviseMode_d) < 3 ? *mReviseMode_d : 2;
    _4c = camera->_860._0;
    const act::Unk_7100922700 initial(camera->_860._0._0 - camera->_860._0._c);
    m47();
    sead::Matrix34f matrix = sead::Matrix34f::ident;
    m48(&matrix);
    sead::Vector3f target;
    matrix.getTranslation(target);
    const act::Unk_7100922700 relative(_4c._0 - target);
    const f32 distance = (_4c._0 - target).length();
    if (distance < *mNear_d) {
        _118 = 0;
        _98 = *mNear_d;
    } else if (distance < *mMiddle_d) {
        _118 = 1;
        _98 = distance;
    } else {
        _118 = distance < *mFar_d ? 3 : 4;
        _98 = *mMiddle_d;
    }
    f32 base_angle = angleStuff(0.0f);
    if (*mBaseAngleCamera_d) {
        base_angle = relative._8;
    } else if (matrix(0, 2) != 0.0f || matrix(2, 2) != 0.0f) {
        base_angle = angleStuff(sead::Mathf::rad2deg(std::atan2(matrix(0, 2), matrix(2, 2))));
    }
    if (*mBack_d)
        sub_7100922600(base_angle);
    const f32 delta = angleStuff(base_angle - initial._8);
    const f32 magnitude = sub_71009226D8(delta);
    const f32 limit = *mAngle_d;
    if (magnitude < limit) {
        _a0 = initial._8;
    } else {
        const f32 sign = angleStuff(delta) < angleStuff(0.0f) ? 1.0f : -1.0f;
        _a0 = angleStuff(base_angle + limit * sign);
    }
    if (_119 == 1) {
        sub_710075C7EC();
    } else {
        sead::Matrix34f latitude_matrix = sead::Matrix34f::ident;
        m48(&latitude_matrix);
        sead::Vector3f latitude_target;
        latitude_matrix.getTranslation(latitude_target);
        const act::Unk_7100922700 latitude(_4c._0 - latitude_target);
        _9c = latitude._4;
    }
    _9c = angleStuff(sead::Mathf::clamp(_9c, _90, _94));
    const f32 fovy_min = sead::Mathf::deg2rad(*mFovyMin_d);
    const f32 fovy_max = sead::Mathf::deg2rad(*mFovyMax_d);
    const f32 fovy = camera->_860._0._24;
    _a4 = fovy < fovy_min ? fovy_min : (fovy_max < fovy ? fovy_max : fovy);
    _88 = 0.0f;
    _8c = 0.0f;
    switch (_118) {
    case 0:
    case 1:
    case 3:
        if (!(*mCount_d <= 0.0f))
            return;
        break;
    }
    camera->sub_71007929E0();
}

// NON_MATCHING: vector interpolation, angle load scheduling and conditional paths differ.
void CameraEventLookBase::m44() {
    auto* camera = getCamera();
    if (!camera)
        return;
    ksys::Timer::update(&_84, 1.0f);
    if (*mCount_d < _84)
        _84 = *mCount_d;
    f32 blend = 1.0f;
    if (_84 < *mCount_d)
        blend = sead::Mathf::clamp(_84 / *mCount_d, 0.0f, 1.0f);
    sead::Matrix34f matrix = sead::Matrix34f::ident;
    m48(&matrix);
    sead::Vector3f target;
    matrix.getTranslation(target);
    act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    const act::Unk_7100922700 initial(_4c._0 - _4c._c);
    switch (_118) {
    case 0:
    case 1:
    case 3:
        if (_84 < *mCount_d) {
            camera->_860._0._c = _4c._c + (target - _4c._c) * blend;
            polar._0 = initial._0 + blend * (_98 - initial._0);
            polar._8 = angleStuff(angleStuff(blend * angleStuff(_a0 - initial._8)) + initial._8);
            polar._4 = angleStuff(angleStuff(blend * angleStuff(_9c - initial._4)) + initial._4);
            camera->_860._0._0 = camera->_860._0._c + polar.sub_7100923254();
            camera->_860._0._24 = _4c._24 + blend * (_a4 - _4c._24);
            if (*mBgHitJump_d && sub_7100925654(&camera->_860._0, camera->_860._38, nullptr)) {
                _84 = *mCount_d;
                camera->sub_71007929E0();
            }
        }
        break;
    }
    bool snap = true;
    switch (_118) {
    case 0:
    case 1:
    case 3:
        snap = _84 >= *mCount_d;
        break;
    }
    if (snap) {
        camera->_860._0._c = target;
        polar._0 = _98;
        polar._8 = _a0;
        polar._4 = _9c;
        camera->_860._0._0 = camera->_860._0._c + polar.sub_7100923254();
        camera->_860._0._24 = _a4;
    }
    if (_84 >= *mCount_d)
        setFinished();
    bool hold_direction = false;
    switch (_118) {
    case 0:
    case 1:
    case 3:
        hold_direction = _84 < *mCount_d;
        break;
    }
    if (hold_direction || _11a == 0)
        camera->_860._818 |= 2;
    else if (_11a != 1)
        camera->_860._818 |= 1;
    camera->_860._6fc = matrix;
}

void CameraEventLookBase::m46() {
    getDynamicParam_2(&mAngle_d, "Angle");
    getDynamicParam_2(&mNear_d, "Near");
    getDynamicParam_2(&mMiddle_d, "Middle");
    getDynamicParam_2(&mFar_d, "Far");
    getDynamicParam_2(&mLatMin_d, "LatMin");
    getDynamicParam_2(&mLatMax_d, "LatMax");
    getDynamicParam_2(&mFovyMin_d, "FovyMin");
    getDynamicParam_2(&mFovyMax_d, "FovyMax");
    getDynamicParam_2(&mCount_d, "Count");
    getDynamicParam_2(&mLatMode_d, "LatMode");
    getDynamicParam_2(&mReviseMode_d, "ReviseMode");
    getDynamicParam_2(&mBaseAngleCamera_d, "BaseAngleCamera");
    getDynamicParam_2(&mBack_d, "Back");
    getDynamicParam_2(&mBgHitJump_d, "BgHitJump");
}

void CameraEventLookBase::m47() {}

void CameraEventLookBase::m48(sead::Matrix34f* mtx) {}

// NON_MATCHING: the original negates and selects the axis words in general registers (eor / csel w); ours mixes
// float and integer selects.
void CameraEventLookBase::sub_710075C7EC() {
    sead::Matrix34f mtx = sead::Matrix34f::zero;
    m48(&mtx);
    sead::Vector3f axis;
    mtx.getBase(axis, 2);
    const sead::Vector3f dir = *mBack_d ? -axis : axis;
    const f32 x = dir.x;
    const f32 y = dir.y;
    const f32 z = dir.z;
    _9c = angleStuff(0.0f);
    if (z != 0.0f || y != 0.0f || x != 0.0f)
        _9c = angleStuff(std::atan2(y, std::sqrt(x * x + z * z)));
    _9c = angleStuff(sead::Mathf::rad2deg(_9c));
}

}  // namespace uking::action
