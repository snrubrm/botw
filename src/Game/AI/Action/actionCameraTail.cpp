#include "Game/AI/Action/actionCameraTail.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include <math/seadMatrixCalcCommon.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

CameraTail::CameraTail(const InitArg& arg) : CameraAction(arg) {}

CameraTail::~CameraTail() = default;

// NON_MATCHING: parameter loads and setup stores are scheduled differently.
void CameraTail::m33() {
    _d8 = sub_7100924D40(*mRadius_s);
    _dc = sub_7100924D40(*mRadiusDolly_s);
    _124 = sead::Mathf::clampMin(*mTargetSpeedMax_s, 0.0f);
    const f32 pan_speed = *mPanSpeedParam_s;
    _120 = 0.4f;
    _1cc = 0;
    _1c8 = pan_speed > 0.0f ? pan_speed : 0.01f;
    sub_7100781F9C();
    sub_71007821D0();
    _e0 = 0.0f;
    sub_7100924C94(sub_7100922348(), sub_7100922354(), &_e8, &_ec);
    _e8 = sead::Mathf::clampMin(_e8, 0.0f);
    _ec = sead::Mathf::clampMin(_ec, 0.0f);
    _f0 = sead::Mathf::clampMin(sub_7100922360(), 0.0f);
    _f4 = sead::Mathf::clamp(sub_710092236C(), 0.0f, 1.0f);
    _12c = 0.0f;
    _e4 = _e8;
    _134 = sead::Matrix33f::ident;
    f32 yaw = 0.0f;
    if (auto* player = sub_7100926A14()) {
        if (player->getMtx()(0, 2) != 0.0f || player->getMtx()(2, 2) != 0.0f)
            yaw = sead::Mathf::rad2deg(std::atan2(player->getMtx()(0, 2), player->getMtx()(2, 2)));
    }
    _158 = angleStuff(yaw);
    _1cd = 5;
    if (auto* camera = getCamera()) {
        _c8 = sub_71009271B0() ? _dc : _d8;
        _cc = (camera->_860._0._0 - camera->_860._0._c).length() - _c8;
        camera->_860._7f8.reset(1);
    }
}

// NON_MATCHING: the slerp arguments use an extra address move.
void CameraTail::sub_71007830FC() {
    if (!(_1cc & 1)) {
        if (auto* player = sub_7100926A14()) {
            sead::Matrix33CalcCommon<f32>::copy(_134, player->getMtx());
            _1cc |= 1;
        }
    }
    if (auto* player = sub_7100926A14())
        sead::Matrix33CalcCommon<f32>::slerpTo(_134, _134,
                                             sead::Matrix33f(player->getMtx()), 0.01f);
}

// NON_MATCHING: state-copy loads and stores have different scheduling.
void CameraTail::sub_7100781F9C() {
    auto* camera = getCamera();
    if (!camera || !camera->_860.sub_710079C184(0x100))
        return;
    if ((camera->_860._0._c - camera->_860._0._0).squaredLength() < 400.0f)
        return;
    camera->_860._a8 = camera->_860._e0;
    camera->_860._70 = camera->_860._e0;
    camera->_860._38 = camera->_860._e0;
    camera->_860._0 = camera->_860._e0;
    act::Unk_7100922700 polar(camera->_860._0._c - camera->_860._0._0);
    polar._0 = _d8;
    camera->_860._0._c = camera->_860._0._0 + polar.sub_7100923254();
}

// NON_MATCHING: clamp comparisons, stack slots and flag updates differ.
void CameraTail::sub_71007821D0() {
    const f32 latitude = *mLatMin_s;
    f32 max = 0.0f;
    f32 min = 0.0f;
    sub_7100924CDC(*mLatMin_s, *mLatMax_s, &min, &max);
    _d4 = sead::Mathf::clamp(latitude, min, max);
    f32 target = 0.0f;
    if (sub_710078469C(&target)) {
        if (!(_1cc & 2) || _d4 <= target)
            _d4 = target;
        else
            _d4 += sub_7100791E44(0.4f) * (target - _d4);
        _1cc |= 2;
    } else {
        _1cc &= ~2;
    }
}

// NON_MATCHING: the original stores _7c / _80 as two 32-bit stores (stp)
bool CameraTail::m32(sead::Heap* heap) {
    const f32 angle = sead::Mathf::deg2rad(*mDstAngle_s);
    _70.z = sead::Mathf::clampMin(_1c8, 0.1f);
    _84 = sead::Mathf::clamp(angle, 0.0f, 1.569051f);
    const f32 tan = std::tan(_84);
    _7c = 0.6;
    _80 = 0.1;
    _88 = tan * _70.z;
    _8c = 1.0;
    _90 = 0.8;
    return true;
}

void CameraTail::m36() {
    getStaticParam(&mLatMin_s, "latMin");
    getStaticParam(&mLatMax_s, "latMax");
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mRadiusDolly_s, "RadiusDolly");
    getStaticParam(&mOffsetYMin_s, "OffsetYMin");
    getStaticParam(&mOffsetYMax_s, "OffsetYMax");
    getStaticParam(&mFovy_s, "Fovy");
    getStaticParam(&mDstAngle_s, "dstAngle");
    getStaticParam(&mPanSpeedParam_s, "PanSpeedParam");
    getStaticParam(&mStartInterpolateParam_s, "StartInterpolateParam");
    getStaticParam(&mResetInterpolateParam_s, "ResetInterpolateParam");
    getStaticParam(&mTargetSpeedMax_s, "TargetSpeedMax");
}

bool CameraTail::sub_71007837D8(const sead::Vector3f& base, f32 a, f32 b, f32 r) {
    const act::Unk_7100922700 polar(r, a, b);
    const sead::Vector3f pos = base + polar.sub_7100923254();
    f32 height = 0;
    if (!sub_71009269F8(pos, &height))
        return false;

    f32 radius;
    if (auto* camera = getCameraActor())
        radius = camera->_860._0.sub_7100921A24(0.1f);
    else
        radius = 0.0f;
    return pos.y < radius + height;
}

void CameraTail::sub_7100783BA8() {
    sub_710078441C();
    _11c = sead::Mathf::clampMin(*mResetInterpolateParam_s, 0.0f);
    _f8.sub_710079C3F8(_11c);
    f32 alignment = 0.0f;
    if (auto* camera = getCamera()) {
        const act::Unk_7100922700 current(camera->_860._0._0 - camera->_860._0._c);
        const act::Unk_7100922700 current_unit(1.0f, current._4, current._8);
        const act::Unk_7100922700 target_unit(1.0f, _b0, _bc);
        const sead::Vector3f current_direction = current_unit.sub_7100923254();
        const sead::Vector3f target_direction = target_unit.sub_7100923254();
        alignment = current_direction.dot(target_direction);
    }
    sub_710074BDF8(alignment);
}

// NON_MATCHING: stack slots, clamp comparisons and paired scalar stores differ.
void CameraTail::sub_710078441C() {
    auto* camera = getCamera();
    if (!camera)
        return;
    auto* player = sub_7100926A14();
    if (!player)
        return;
    sead::Vector3f forward;
    player->getMtx().getBase(forward, 2);
    const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    const f32 elevation = sead::Mathf::rad2deg(std::atan2(-forward.y,
        std::sqrt(forward.x * forward.x + forward.z * forward.z)));
    const f32 latitude = sead::Mathf::clampMin(elevation, _d4);
    f32 min = 0.0f;
    f32 max = 0.0f;
    sub_7100924CDC(*mLatMin_s, *mLatMax_s, &min, &max);
    _b0 = sead::Mathf::clamp(latitude, min, max);
    _b4 = 0.0f;
    _b8 = angleStuff(polar._4 - _b0);
    sub_7100784288();
    f32 yaw;
    if (player->m187()) {
        yaw = player->_e50;
    } else {
        f32 angle = 0.0f;
        if (auto* current_player = sub_7100926A14()) {
            if (current_player->getMtx()(0, 2) != 0.0f || current_player->getMtx()(2, 2) != 0.0f)
                angle = sead::Mathf::rad2deg(std::atan2(current_player->getMtx()(0, 2),
                                                      current_player->getMtx()(2, 2)));
        }
        const f32 normalized_angle = angleStuff(angle);
        yaw = sub_7100922530(normalized_angle);
    }
    _bc = angleStuff(yaw);
    _c0 = 0.0f;
    _c4 = angleStuff(polar._8 - _bc);
    _f8.sub_710079C384(10.0f, 0.0f);
    _4c = sead::Vector3f::zero;
    _58 = sead::Vector3f::zero;
    _64 = sead::Vector3f::zero;
    _70 = sead::Vector3f(0.0f, 0.0f, sead::Mathf::clampMin(_1c8, 0.1f));
    _84 = sead::Mathf::clamp(sead::Mathf::deg2rad(*mDstAngle_s), 0.0f, 1.569051f);
    _88 = std::tan(_84) * _70.z;
    _7c = 0.6f;
    _80 = 0.1f;
    _8c = 1.0f;
    _90 = 0.8f;
}

f32 CameraTail::sub_7100784288() {
    auto* camera = getCamera();
    if (!camera || !sub_7100926A14())
        return 0.0f;
    _f8.sub_710079C3F8(1.0f);
    const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    sub_710078483C(&_98);
    if (sub_7100926A14()) {
        f32 height = 0.0f;
        if (sub_71009269F8(_98, &height)) {
            f32 radius = 0.0f;
            if (auto* actor = getCameraActor())
                radius = actor->_860._0.sub_7100921A24(0.1f);
            _98.y = _98.y > radius + height ? _98.y : radius + height;
        }
    }
    _a4 = camera->_860._0._c - _98;
    const f32 speed = _a4 == sead::Vector3f(0.0f, 0.0f, 0.0f) ? 0.0f :
        std::fmax(_a4.length() * 10.0f, 10.0f);
    _d0 = camera->_860._0._24 - *mFovy_s;
    return speed;
}

// NON_MATCHING: the initial angle sum is scheduled after the polar constructor.
void CameraTail::sub_710078483C(sead::Vector3f* out) {
    *out = _98;
    if (auto* camera = getCameraActor()) {
        *out = camera->_860._2b8;
        f32 max = 0.0f;
        f32 min = 0.0f;
        sub_7100924CDC(*mLatMin_s, *mLatMax_s, &min, &max);
        if (min != max) {
            const act::Unk_7100922700 polar(_70 - _64);
            out->y += *mOffsetYMin_s + ((_b0 + _b4 + polar._4) - max) / (min - max) *
                (*mOffsetYMax_s - *mOffsetYMin_s);
        }
    }
}

// NON_MATCHING: stack slots and clamp comparison operands differ.
bool CameraTail::sub_710078469C(f32* out) {
    if (!getCameraActor())
        return false;
    sead::Vector3f pos = sead::Vector3f::zero;
    sub_710078483C(&pos);
    if (pos.isNan() || !sub_7100926A14())
        return false;
    f32 height = 0.0f;
    if (sub_71009269F8(pos, &height)) {
        const f32 rate = sead::Mathf::clamp(((pos.y - height) - 1.0f) / 5.0f, 0.0f, 1.0f);
        const f32 latitude = *mLatMin_s;
        f32 max = 0.0f;
        f32 min = 0.0f;
        sub_7100924CDC(*mLatMin_s, *mLatMax_s, &min, &max);
        *out = rate * sead::Mathf::clamp(latitude, min, max);
    } else {
        const f32 latitude = *mLatMin_s;
        f32 max = 0.0f;
        f32 min = 0.0f;
        sub_7100924CDC(*mLatMin_s, *mLatMax_s, &min, &max);
        *out = sead::Mathf::clamp(latitude, min, max);
    }
    return true;
}

// NON_MATCHING: the original keeps the delta in a register across the sqrt call (ours reloads it from the stack) and
// returns through a shared zero (s8) set at the top.
f32 CameraTail::sub_7100784940() {
    f32 speed = 0.0f;
    if (!(_12c < 20.0f)) {
        if (auto* camera = getCameraActor()) {
            if (auto* player = sub_7100926A14()) {
                const sead::Vector3f pos(player->getMtx().m[0][3], player->getMtx().m[1][3],
                                         player->getMtx().m[2][3]);
                f32 dt = 0.0f;
                ksys::Timer::update(&dt, 1.0f);
                if (dt != 0.0f) {
                    const f32 dist = (pos - sub_7100928868(camera->_860._164)).length();
                    const f32 value = dist / dt;
                    speed = value > _124 ? _124 : value;
                }
            }
        }
    }
    return speed;
}

}  // namespace uking::action
