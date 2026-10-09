#include "Game/AI/Action/actionCameraTail.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include <math/seadMatrixCalcCommon.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/ActorSystem/actUnk_71024ef4e8.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

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

// NON_MATCHING: state transitions, vector copies and scalar scheduling differ.
void CameraTail::m34() {
    auto* camera = getCamera();
    if (!camera)
        return;
    auto* player = sub_7100926A14();
    if (!player)
        return;
    if (!(_1cc & 4) && sub_71009271B0())
        _1cc |= 4;
    if (_12c < 3000.0f) {
        ksys::Timer::update(&_12c, 1.0f);
        if (_12c > 3000.0f)
            _12c = 3000.0f;
    }
    f32 target_latitude = 0.0f;
    if (sub_710078469C(&target_latitude)) {
        if (!(_1cc & 2) || _d4 <= target_latitude)
            _d4 = target_latitude;
        else
            _d4 += sub_7100791E44(0.4f) * (target_latitude - _d4);
        _1cc |= 2;
    } else {
        _1cc &= ~2;
    }
    if (_1cd < 6 && ((1 << _1cd) & 0x31)) {
        if (auto* current_player = sub_7100926A14()) {
            sead::Matrix33CalcCommon<f32>::copy(_134, current_player->getMtx());
            _1cc |= 1;
        }
    } else {
        sub_71007830FC();
    }
    f32 move_angle = 0.0f;
    bool moving;
    if (player->m191()) {
        moving = true;
    } else {
        moving = player->m187() ? player->m261(&move_angle) : player->m258(&move_angle);
        move_angle = -move_angle;
    }
    const act::Unk_7100922700 previous_polar(camera->_860._0._0 - camera->_860._0._c);
    auto polar = previous_polar;
    sead::Vector2f stick;
    sub_7100924F08(&stick);
    const f32 stick_length = stick.length();
    const f32 stick_angle = std::atan2(stick.y, stick.x);
    const u8 previous_state = _1cd;
    sub_71007831EC();
    if (previous_state != _1cd) {
        if (_1cd == 2) {
            if (auto* current_player = sub_7100926A14()) {
                sead::Matrix33CalcCommon<f32>::copy(_134, current_player->getMtx());
                _1cc |= 1;
            }
        }
        switch (_1cd) {
        case 0: sub_7100783A0C(); break;
        case 1:
            sub_710078441C();
            _118 = sead::Mathf::clampMin(*mStartInterpolateParam_s, 0.0f);
            _f8.sub_710079C3F8(_118);
            break;
        case 2: sub_7100783BA8(); break;
        case 3: sub_7100783CA4(); break;
        default: sub_71007840E0(); break;
        }
    }
    const sead::Vector3f forward(_134(0, 2), _134(1, 2), _134(2, 2));
    sead::Vector3f pan_delta(0.0f, 0.0f, 1.0f);
    const sead::Vector3f previous_pan_delta = mPan._24 - mPan._18;
    if (_1cd >= 1 && _1cd <= 3)
        sub_7100783380(move_angle, moving, &pan_delta);
    act::Unk_7100922700 pan(pan_delta);
    const act::Unk_7100922700 previous_pan(previous_pan_delta);
    const f32 old_progress = _f8._18;
    _f8.sub_710079C408();
    const f32 progress = _f8._18;
    if (old_progress < 1.0f && progress >= 1.0f && _1cd == 2)
        sub_710074BCB4();
    f32 frame = 0.0f;
    ksys::Timer::update(&frame, 1.0f);
    sub_7100783578();
    ksys::VFR::chase(&_d0, 0.0f, sub_7100924D80(0.1f));
    const f32 remaining = 1.0f - progress;
    camera->_860._0._24 = *mFovy_s + remaining * _d0;
    sead::Vector3f target = sead::Vector3f::zero;
    sub_710078483C(&target);
    if (sub_7100926A14()) {
        f32 height = 0.0f;
        if (sub_71009269F8(target, &height)) {
            auto* camera_actor = getCameraActor();
            const f32 margin = camera_actor ? camera_actor->_860._0.sub_7100921A24(0.1f) : 0.0f;
            target.y = target.y > margin + height ? target.y : margin + height;
        }
    }
    if (player->getRootAi() && player->getRootAi()->isCurrentAction("よじ登り飛びつき"))
        _120 = 0.06f;
    else
        ksys::VFR::lerp(&_120, 0.4f, 0.1f);
    ksys::VFR::lerp(&_98, target, _120);
    camera->_860._0._c = _98 + _a4 * (1.0f - progress * progress);
    sub_7100924C94(sub_7100922348(), sub_7100922354(), &_e8, &_ec);
    _e8 = sead::Mathf::clampMin(_e8, 0.0f);
    _ec = sead::Mathf::clampMin(_ec, 0.0f);
    _f0 = sead::Mathf::clampMin(sub_7100922360(), 0.0f);
    _f4 = sead::Mathf::clamp(sub_710092236C(), 0.0f, 1.0f);
    sub_7100783688(moving);
    if ((_1cc & 4) || moving || polar._0 < 3.0f) {
        f32 radius_delta = _cc;
        const f32 rate = sub_7100924D80(0.1f);
        if (_1cc & 4)
            ksys::VFR::lerp(&radius_delta, 0.0f, rate);
        else
            ksys::VFR::lerp(&radius_delta, 0.0f, rate, _e4);
        f32 radius = _c8;
        const f32 radius_target = sub_71009271B0() ? _dc : _d8;
        ksys::VFR::lerp(&radius, radius_target, sub_7100924D80(0.1f));
        const f32 new_radius = sub_7100924D40(radius_delta + radius);
        if (!sub_71007837D8(camera->_860._0._c, polar._4, polar._8, new_radius)) {
            polar._0 = new_radius;
            _c8 = radius;
            _cc = radius_delta;
        } else {
            _e4 = _e8;
        }
    }
    const f32 radius_difference = polar._0 - previous_polar._0;
    _e0 = radius_difference > 0.0f ? radius_difference : -radius_difference;
    if (_1cd == 4) {
        _bc = angleStuff(angleStuff(_bc) + frame * stick_length * std::cos(stick_angle) *
                         sub_71009272A8() * sub_7100927230());
    } else {
        angleStuff(0.0f);
        f32 yaw = 0.0f;
        const bool special_movement = player->m187();
        if (_1cd == 0 && !special_movement) {
            yaw = _158;
        } else {
            if (special_movement) {
                yaw = player->_e50;
            } else {
                if (auto* current_player = sub_7100926A14()) {
                    const auto& matrix = current_player->getMtx();
                    if (matrix(0, 2) != 0.0f || matrix(2, 2) != 0.0f)
                        yaw = sead::Mathf::rad2deg(std::atan2(matrix(0, 2), matrix(2, 2)));
                }
                yaw = angleStuff(yaw);
                yaw = sub_7100922530(yaw);
            }
            yaw = angleStuff(yaw);
        }
        const f32 rate = sub_7100791E44(0.1f);
        const f32 current_yaw = angleStuff(_bc);
        _bc = angleStuff(current_yaw + angleStuff(rate * angleStuff(yaw - current_yaw)));
        if (moving)
            _c0 += sub_710092523C(sub_71009251C4(getCameraActor()), 0.05f) * (0.0f - _c0);
    }
    polar._8 = angleStuff(pan._8 + _bc + _c0 + remaining * _c4);
    f32 latitude;
    if (_1cd == 4) {
        _b0 += frame * stick_length * std::sin(stick_angle) * sub_7100927238() * sub_7100927228();
        f32 min = 0.0f, max = 0.0f;
        sub_7100924CDC(*mLatMin_s, *mLatMax_s, &min, &max);
        latitude = sead::Mathf::clamp(_b0, min, max);
    } else {
        if (moving)
            _b4 += sub_710092523C(sub_71009251C4(getCameraActor()), 0.05f) * (0.0f - _b4);
        const f32 elevation = _1cd == 0 ? 0.0f : sead::Mathf::rad2deg(
            std::atan2(-forward.y, std::sqrt(forward.x * forward.x + forward.z * forward.z)));
        const f32 target_lat = elevation < _d4 ? _d4 : elevation;
        if (angleStuff(pan._4) < angleStuff(previous_pan._4)) {
            const f32 candidate = angleStuff(pan._4 + target_lat + _b4);
            f32 min = 0.0f, max = 0.0f;
            sub_7100924CDC(*mLatMin_s, *mLatMax_s, &min, &max);
            if (sub_71007837D8(camera->_860._0._c, sead::Mathf::clamp(candidate, min, max),
                                 polar._8, polar._0)) {
                const sead::Vector3f delta = mPan._24 - mPan._18;
                const f32 distance = std::sqrt(delta.x * delta.x + delta.z * delta.z);
                mPan._24.y = mPan._18.y + std::tan(sead::Mathf::deg2rad(previous_pan._4)) * distance;
                pan.set(mPan._24 - mPan._18);
            }
        }
        latitude = _b0 + sub_7100791E44(0.1f) * (target_lat - _b0);
    }
    _b0 = latitude;
    polar._4 = angleStuff(sub_7100924CAC(angleStuff(pan._4 + latitude + _b4 + remaining * _b8)));
    camera->_860._0._0 = camera->_860._0._c + polar.sub_7100923254();
    if (_1cd == 4)
        camera->_860._7f8.set(1);
    else
        camera->_860._7f8.reset(1);
    camera->_860._4f4 = sub_7100922144();
    camera->sub_71007953C8();
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

// NON_MATCHING: the original stores mPan._30 / mPan._34 as two 32-bit stores (stp)
bool CameraTail::m32(sead::Heap* heap) {
    const f32 angle = sead::Mathf::deg2rad(*mDstAngle_s);
    mPan._24.z = sead::Mathf::clampMin(_1c8, 0.1f);
    mPan._38 = sead::Mathf::clamp(angle, 0.0f, 1.569051f);
    const f32 tan = std::tan(mPan._38);
    mPan._30 = 0.6;
    mPan._34 = 0.1;
    mPan._3c = tan * mPan._24.z;
    mPan._40 = 1.0;
    mPan._44 = 0.8;
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
    mPan._0 = sead::Vector3f::zero;
    mPan._c = sead::Vector3f::zero;
    mPan._18 = sead::Vector3f::zero;
    mPan._24 = sead::Vector3f(0.0f, 0.0f, sead::Mathf::clampMin(_1c8, 0.1f));
    mPan._38 = sead::Mathf::clamp(sead::Mathf::deg2rad(*mDstAngle_s), 0.0f, 1.569051f);
    mPan._3c = std::tan(mPan._38) * mPan._24.z;
    mPan._30 = 0.6f;
    mPan._34 = 0.1f;
    mPan._40 = 1.0f;
    mPan._44 = 0.8f;
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
            const act::Unk_7100922700 polar(mPan._24 - mPan._18);
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

// NON_MATCHING: state branches, camera getter scheduling and chase scalar loads differ.
void CameraTail::sub_71007831EC() {
    sead::Vector2f stick(0.0f, 0.0f);
    sub_7100924F08(&stick);
    if (stick.x != 0.0f || stick.y != 0.0f) {
        _1cd = 4;
        return;
    }
    if (sub_7100927110()) {
        _1cd = 2;
        return;
    }
    if (_1cd == 1 || _1cd == 2) {
        if (!(_f8._18 >= 1.0f))
            return;
    } else if (_1cd == 5) {
        _1cd = 1;
        auto* player = sub_7100926A14();
        if (!player)
            return;
        auto* attachment = player->getAttachedTargetActor();
        if (!attachment || !attachment->mAttachInfo)
            return;
        if (attachment->mAttachInfo->_138 == 1)
            _1cd = 0;
        return;
    } else if (_1cd == 0) {
        if (!(_130 > 0.0f)) {
            auto* player = sub_7100926A14();
            if (!player)
                return;
            auto* attachment = player->getAttachedTargetActor();
            if (!attachment || !attachment->mAttachInfo || attachment->mAttachInfo->_138 == 1)
                return;
            _130 = 20.0f;
            return;
        }
        if (!sead::Mathf::chase(&_130, 0.0f, sub_71009251C4(getCamera())))
            return;
    } else {
        return;
    }
    _1cd = 3;
}

// NON_MATCHING: player position capture, frame and bound scalar scheduling differ.
void CameraTail::sub_7100783578() {
    _128 = 0.0f;
    if (!(_12c >= 20.0f))
        return;
    auto* camera = getCamera();
    if (!camera)
        return;
    auto* player = sub_7100926A14();
    if (!player)
        return;
    const sead::Vector3f position = player->getMtx().getTranslation();
    f32 frame = 0.0f;
    ksys::Timer::update(&frame, 1.0f);
    if (frame != 0.0f) {
        _128 = ((position - sub_7100928868(camera->_860._164)).length() / frame - 0.05f) / 0.05f;
        if (_128 < 0.0f)
            _128 = 0.0f;
        else if (_128 > 1.0f)
            _128 = 1.0f;
    }
}

// NON_MATCHING: chase branches and scalar scheduling differ.
void CameraTail::sub_7100783688(bool chase) {
    _e4 = _e0;
    if (_e4 < _e8)
        _e4 = _e8;
    else if (_e4 > _ec)
        _e4 = _ec;
    if (chase)
        ksys::VFR::chase(&_e4, _ec, _f0);
    else
        ksys::VFR::lerp(&_e4, _e8, _f4);
}

// NON_MATCHING: prepared-field loads, vector resets and float scheduling differ.
void CameraTail::sub_7100783A0C() {
    auto* camera = getCamera();
    if (!camera)
        return;
    const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    _b0 = _b4 = 0.0f;
    _b8 = angleStuff(polar._4);
    sub_7100784288();
    _bc = _158;
    if (auto* player = sub_7100926A14()) {
        if (player->m187())
            _bc = player->_e50;
    }
    _c0 = 0.0f;
    _c4 = angleStuff(polar._8 - _bc);
    _f8.sub_710079C384(10.0f, 0.0f);
    const f32 angle = *mDstAngle_s * 0.017453292f;
    mPan._0 = sead::Vector3f::zero;
    mPan._18 = sead::Vector3f::zero;
    mPan._24.set(0.0f, 0.0f, sead::Mathf::clampMin(_1c8, 0.1f));
    mPan._c = sead::Vector3f::zero;
    mPan._38 = angle;
    if (mPan._38 < 0.0f)
        mPan._38 = 0.0f;
    else if (mPan._38 > 1.569051f)
        mPan._38 = 1.569051f;
    mPan._3c = std::tan(mPan._38) * mPan._24.z;
    mPan._30 = 0.6f;
    mPan._34 = 0.1f;
    mPan._40 = 1.0f;
    mPan._44 = 0.8f;
    _130 = 0.0f;
}

// NON_MATCHING: bound and prepared-field loads, vector resets and float scheduling differ.
void CameraTail::sub_71007840E0() {
    auto* camera = getCamera();
    if (!camera)
        return;
    const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    f32 min = 0.0f;
    f32 max = 0.0f;
    sub_7100924CDC(*mLatMin_s, *mLatMax_s, &min, &max);
    _b0 = sead::Mathf::clamp(polar._4, min, max);
    _b4 = 0.0f;
    _b8 = angleStuff(polar._4 - _b0);
    _c0 = _c4 = 0.0f;
    _bc = polar._8;
    const f32 angle = *mDstAngle_s * 0.017453292f;
    mPan._0 = sead::Vector3f::zero;
    mPan._18 = sead::Vector3f::zero;
    mPan._24.set(0.0f, 0.0f, sead::Mathf::clampMin(_1c8, 0.1f));
    mPan._c = sead::Vector3f::zero;
    mPan._38 = angle;
    if (mPan._38 < 0.0f)
        mPan._38 = 0.0f;
    else if (mPan._38 > 1.569051f)
        mPan._38 = 1.569051f;
    mPan._3c = std::tan(mPan._38) * mPan._24.z;
    mPan._30 = 0.6f;
    mPan._34 = 0.1f;
    mPan._40 = 1.0f;
    mPan._44 = 0.8f;
    _f8.sub_710079C384(sub_7100784288(), 0.0f);
    sub_710074BCB4();
}

// NON_MATCHING: scalar and vector copies have different scheduling.
void CameraTail::PanState::sub_7100784D38(f32 speed, f32 direction) {
    if (speed > 0.0f)
        _0 += sead::Vector3f(-std::sin(direction), std::cos(direction), 0.0f) * speed;
    _c += (_0 - _c) * _30;
    const sead::Vector3f delta = _18 - _c;
    const f32 length = delta.length();
    if (_34 < length) {
        sead::Vector3f offset = (delta * (1.0f / length)) * _34;
        offset.z = 0.0f;
        _18 = _c + offset;
    }
}

// NON_MATCHING: bound loads, overshoot correction and vector copies differ.
void CameraTail::PanState::sub_7100784A20(const Params& params, sead::Vector3f* out) {
    const f32 radius = sead::Mathf::clampMin(params.radius, 0.1f);
    if (radius != _24.z) {
        const f32 scale = radius / _24.z;
        _24.x = _18.x + scale * (_24.x - _18.x);
        _24.y = _18.y + scale * (_24.y - _18.y);
        _24.z = radius;
    }
    _38 += (sead::Mathf::clamp(params.angle, 0.0f, 1.569051f) - _38) * 0.1f;
    _3c = std::tan(_38) * _24.z;
    _34 += (std::fmax(params.distance, 0.0f) - _34) * 0.1f;
    _30 = sead::Mathf::clamp(params.follow_rate, 0.0f, 1.0f);
    _40 = std::fmax(params.exponent, 0.0f);
    _44 = std::fmax(params.damping, 0.0f);
    const sead::Vector3f previous = _18;
    sub_7100784D38(params.speed, params.direction);
    const f32 old_x = previous.x - _24.x;
    const f32 new_x = _18.x - _24.x;
    const f32 old_y = previous.y - _24.y;
    const f32 new_y = _18.y - _24.y;
    f32 correction_x = 0.0f;
    if (!(old_x * new_x <= 0.0f) && _3c != 0.0f) {
        const f32 old_abs = old_x > 0.0f ? old_x : -old_x;
        const f32 new_abs = new_x > 0.0f ? new_x : -new_x;
        if (!(old_abs <= new_abs))
            correction_x = (old_x - new_x) * _44 * std::pow(new_abs / _3c, _40);
    }
    _24.x += correction_x;
    f32 correction_y = 0.0f;
    if (!(old_y * new_y <= 0.0f) && _3c != 0.0f) {
        const f32 old_abs = old_y > 0.0f ? old_y : -old_y;
        const f32 new_abs = new_y > 0.0f ? new_y : -new_y;
        if (!(old_abs <= new_abs))
            correction_y = (old_y - new_y) * _44 * std::pow(new_abs / _3c, _40);
    }
    _24.y += correction_y;
    const sead::Vector3f center(_18.x, _18.y, _24.z);
    const sead::Vector3f delta = _24 - center;
    const f32 length = delta.length();
    if (_3c < length) {
        sead::Vector3f offset = (delta * (1.0f / length)) * _3c;
        offset.z = 0.0f;
        _24 = center + offset;
    }
    const sead::Vector3f origin = _0;
    _0 -= origin;
    _c -= origin;
    _18 -= origin;
    _24 -= origin;
    *out = _24 - _18;
}

// NON_MATCHING: chase branches, scalar/vector copies and parameter stores differ.
void CameraTail::sub_7100783380(f32 angle, bool move, sead::Vector3f* out) {
    if (_cc >= -1.1920929e-7f && _cc <= 1.1920929e-7f)
        ksys::VFR::chase(&_94, 1.0f, 0.05f);
    else
        _94 = 0.35f;
    PanState::Params params{0.0f, angle, _1c8, sead::Mathf::deg2rad(*mDstAngle_s),
                            0.6f, 0.1f, 1.0f, 0.8f};
    const f32 speed = sub_7100784940();
    sead::Vector3f velocity(0.0f, std::sin(angle), std::cos(angle));
    velocity *= speed;
    velocity.z *= _94;
    if (move && velocity != sead::Vector3f::zero) {
        params.speed = velocity.length();
        params.direction = std::atan2(-velocity.y, velocity.z);
    }
    mPan.sub_7100784A20(params, out);
}

// NON_MATCHING: polar/vector copies, bound loads and scalar scheduling differ.
void CameraTail::sub_7100783CA4() {
    auto* camera = getCamera();
    if (!camera)
        return;
    const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    const sead::Vector3f forward = _134.getBase(2);
    const f32 elevation = std::atan2(-forward.y, std::sqrt(forward.x * forward.x +
                                                        forward.z * forward.z)) * 57.295776f;
    const f32 latitude = elevation < _d4 ? _d4 : elevation;
    f32 min = 0.0f;
    f32 max = 0.0f;
    sub_7100924CDC(*mLatMin_s, *mLatMax_s, &min, &max);
    _b0 = sead::Mathf::clamp(latitude, min, max);
    sub_7100924CDC(*mLatMin_s, *mLatMax_s, &min, &max);
    _b8 = angleStuff(polar._4 - sead::Mathf::clamp(polar._4, min, max));
    f32 yaw = 0.0f;
    if (auto* player = sub_7100926A14()) {
        const sead::Vector3f player_forward = player->getMtx().getBase(2);
        if (player_forward.x != 0.0f || player_forward.z != 0.0f)
            yaw = std::atan2(player_forward.x, player_forward.z) * 57.295776f;
    }
    yaw = angleStuff(yaw);
    _bc = sub_7100922530(yaw);
    _c4 = 0.0f;
    mPan._0 = sead::Vector3f::zero;
    mPan._18 = sead::Vector3f::zero;
    mPan._24.set(0.0f, 0.0f, sead::Mathf::clampMin(_1c8, 0.1f));
    mPan._c = sead::Vector3f::zero;
    mPan._38 = sead::Mathf::clamp(sead::Mathf::deg2rad(*mDstAngle_s), 0.0f, 1.569051f);
    mPan._3c = std::tan(mPan._38) * mPan._24.z;
    mPan._30 = 0.6f;
    mPan._34 = 0.1f;
    mPan._40 = 1.0f;
    mPan._44 = 0.8f;
    const f32 pitch_delta = sead::Mathf::deg2rad(angleStuff(polar._4 - _b0));
    const f32 yaw_delta = sead::Mathf::deg2rad(angleStuff(polar._8 - _bc));
    mPan._24.x = std::tan(sead::Mathf::clamp(yaw_delta, -mPan._38, mPan._38)) * mPan._24.z;
    mPan._24.y = std::tan(sead::Mathf::clamp(pitch_delta, -mPan._38, mPan._38)) * mPan._24.z;
    const sead::Vector3f center(mPan._18.x, mPan._18.y, mPan._24.z);
    const sead::Vector3f delta = mPan._24 - center;
    const f32 length = delta.length();
    if (mPan._3c < length) {
        sead::Vector3f offset = (delta * (1.0f / length)) * mPan._3c;
        offset.z = 0.0f;
        mPan._24 = center + offset;
    }
    const act::Unk_7100922700 pan(mPan._24 - mPan._18);
    sub_7100924CDC(*mLatMin_s, *mLatMax_s, &min, &max);
    _b4 = angleStuff(angleStuff(sead::Mathf::clamp(polar._4, min, max) - _b0) - pan._4);
    _c0 = angleStuff(angleStuff(polar._8 - _bc) - pan._8);
    _f8.sub_710079C384(sub_7100784288(), 0.0f);
    sub_710074BCB4();
}

}  // namespace uking::action
