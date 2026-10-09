#include "Game/AI/Action/actionCameraAiming.h"
#include <math/seadMathCalcCommon.h>
#include <cmath>
#include <algorithm>
#include "KingSystem/System/Timer.h"
#include "KingSystem/System/VFRValue.h"
#include "KingSystem/Utils/MathUtil.h"
#include "Game/Actor/actMotorcycle.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::action {

CameraAiming::CameraAiming(const InitArg& arg) : CameraAction(arg) {}

CameraAiming::~CameraAiming() = default;

// NON_MATCHING: accessor lifetimes and motion response scheduling differ.
void CameraAiming::m33() {
    sub_7100924CDC(*mLatMin_s, *mLatMax_s, &_280, &_284);
    auto* camera = getCamera();
    if (!camera)
        return;
    const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    ksys::act::acc::PlayerBase player;
    sub_7100926A50(&player);
    if (!player.hasProc())
        return;
    _28b = 0;
    if (sub_7100926D24())
        _28b = player.x_21() || (mBowFlag_s && *mBowFlag_s && player.x_38());
    sead::Matrix34f transform = sead::Matrix34f::ident;
    sub_710074DAE8(&transform);
    sub_710074DBD0(transform, &_17c);
    _170.setMul(transform, _17c);
    sead::Vector3f offset = sead::Vector3f::zero;
    sub_710074DD28(polar, &offset);
    _170 += offset;
    sub_710074C97C();
    _74.sub_71008A4644();
    _160 = 0;
    _164 = 0.0f;
    if (sub_7100925110(_74._0, 0))
        _160 = 0;
    else if (sub_7100925110(_74._0, 1))
        _160 = 1;
    else if (sub_7100925110(_74._0, 2))
        _160 = 2;
    _168 = 0.0f;
    _16c = 0.0f;
    _289 = 2;
    _28a = 2;
    ksys::act::ActorConstDataAccess target;
    {
        ksys::act::acc::PlayerBase current_player;
        sub_7100926A50(&current_player);
        if (current_player.hasProc()) {
            if (current_player.x_21())
                target.acquireActor(current_player);
            else
                sub_710074E3EC(&target);
        }
    }
    if (!target.hasProc())
        return;
    const auto& target_transform = target.getActorMtx();
    f32 yaw = 0.0f;
    if (target_transform(0, 2) != 0.0f || target_transform(2, 2) != 0.0f)
        yaw = sead::Mathf::rad2deg(std::atan2(target_transform(0, 2), target_transform(2, 2)));
    _1c8 = angleStuff(yaw);
    f32 elapsed = 0.0f;
    ksys::Timer::update(&elapsed, 1.0f);
    if (elapsed == 0.0f)
        return;
    const sead::Vector3f translation = camera->_860._270.getTranslation();
    const sead::Vector3f displacement = translation - sub_7100928868(camera->_860._164);
    const f32 inv_elapsed = 1.0f / elapsed;
    const f32 horizontal_speed = inv_elapsed * std::sqrt(
        displacement.x * displacement.x + displacement.z * displacement.z);
    const sead::Vector3f previous_displacement = sub_7100928868(camera->_860._174);
    const f32 horizontal_acceleration = inv_elapsed * std::sqrt(
        sead::Mathf::square(displacement.x - previous_displacement.x) +
        sead::Mathf::square(displacement.z - previous_displacement.z));
    const f32 horizontal_phase = std::min(sead::Mathf::abs(horizontal_speed), 0.5f) *
                                 2.0f * sead::Mathf::pi() - sead::Mathf::pi() * 0.5f;
    const f32 horizontal_blend = (std::sin(horizontal_phase) + 1.0f) * 0.5f;
    _198 = _188 + horizontal_blend * (_18c - _188);
    _19c = 0.1f + std::min(sead::Mathf::abs(horizontal_acceleration), 0.05f) / 0.05f * 0.8f;
    const f32 vertical_acceleration = inv_elapsed * sead::Mathf::abs(
        displacement.y - sub_7100928868(camera->_860._174).y);
    const f32 vertical_speed = inv_elapsed * sead::Mathf::abs(displacement.y);
    const f32 vertical_phase = std::min(sead::Mathf::abs(vertical_speed), 1.0f) *
                               sead::Mathf::pi() - sead::Mathf::pi() * 0.5f;
    const f32 vertical_blend = (std::sin(vertical_phase) + 1.0f) * 0.5f;
    _1a0 = _190 + vertical_blend * (_194 - _190);
    _1a4 = 0.1f + std::min(sead::Mathf::abs(vertical_acceleration), 0.05f) / 0.05f * 0.8f;
    if (camera->_860._7fc.sub_710079C0CC(0x100000)) {
        _1a8.sub_710079C510(1.0f);
        camera->_860._0._c = _170;
        const act::Unk_7100922700 direction(_4c, _150, _154);
        camera->_860._0._0 = camera->_860._0._c + direction.sub_7100923254();
        camera->_860._0._24 = _6c;
        camera->_860._0._28 = 0.0f;
    }
}

// NON_MATCHING: input/accessor lifetimes, motion snapshots and scalar scheduling differ.
void CameraAiming::m34() {
    sub_7100924CDC(*mLatMin_s, *mLatMax_s, &_280, &_284);
    auto* camera = getCamera();
    if (!camera)
        return;
    const act::Unk_7100922700 initial(camera->_860._0._0 - camera->_860._0._c);
    act::Unk_7100922700 polar = initial;
    ksys::act::acc::PlayerBase player;
    sub_7100926A50(&player);
    if (!player.hasProc())
        return;
    const sead::Vector3f translation = camera->_860._270.getTranslation();
    ksys::act::ActorConstDataAccess target;
    {
        ksys::act::acc::PlayerBase current_player;
        sub_7100926A50(&current_player);
        if (current_player.hasProc()) {
            if (current_player.x_21())
                target.acquireActor(current_player);
            else
                sub_710074E3EC(&target);
        }
    }
    if (!target.hasProc())
        return;
    const auto& transform = target.getActorMtx();
    if (ksys::util::sub_71011F10F4(transform))
        return;
    f32 elapsed = 0.0f;
    ksys::Timer::update(&elapsed, 1.0f);
    if (elapsed == 0.0f)
        return;
    sead::Vector2f stick = sead::Vector2f::zero;
    sub_7100924F08(&stick);
    _289 = 0;
    if (stick.x == 0.0f && stick.y == 0.0f &&
        (*mGyro_s != 1 && (*mGyro_s != 2 || sub_710092732C())))
        _289 = 1;
    sead::Matrix33f gyro = sead::Matrix33f::ident;
    if (_289) {
        _74.sub_71008A4694(0.0f);
        gyro = _74._0;
        // Native relative-matrix call is retained although this caller does not read its output.
        sub_71009238F8(&gyro, _74._b4);
    } else {
        _74.sub_71008A4644();
    }
    _1a8.sub_710079C3F8(sead::Mathf::clampMin(*mConnect_s, 0.0f));
    _1a8.sub_710079C408();
    const f32 blend = 1.0f - _1a8._18;
    if (_289) {
        _150 = angleStuff(_150 + sead::Mathf::rad2deg(sub_7100923A38(_74._0, _74._24, 2, 0)) *
                                    *mLatGyroScale_s);
        _168 = 0.5f;
    } else {
        const f32 input = sub_7100927228() * sub_7100927238() * *mLatStickScale_s * stick.y;
        const f32 sign = input > 0.0f ? 1.0f : -1.0f;
        ksys::VFRValue scaled(sead::Mathf::abs(input));
        scaled.updateStats();
        _150 = angleStuff(_158 + sign * scaled.mean);
        _168 = 1.0f;
    }
    _150 = angleStuff(sead::Mathf::clamp(_150, _280, _284));
    const f32 latitude_rate = sub_7100791E44(_168);
    _158 = angleStuff(_158 + angleStuff(latitude_rate * angleStuff(_150 - _158)));
    polar._4 = angleStuff(sub_7100924CAC(angleStuff(_158 + angleStuff(blend * _15c))));
    f32 yaw = angleStuff(0.0f);
    if (transform(0, 2) != 0.0f || transform(2, 2) != 0.0f)
        yaw = angleStuff(sead::Mathf::rad2deg(std::atan2(transform(0, 2), transform(2, 2))));
    const f32 yaw_delta = angleStuff(yaw - _1c8);
    if (_289) {
        _154 = angleStuff(_154 + sub_7100923E2C() * *mLngGyroScale_s);
        const f32 rate = sub_7100791E44(0.5f);
        polar._8 = angleStuff(polar._8 + angleStuff(rate * angleStuff(_154 - polar._8)));
    } else {
        const f32 input = sub_7100927230() * sub_71009272A8() * *mLngStickScale_s * stick.x;
        const f32 sign = input > 0.0f ? 1.0f : -1.0f;
        ksys::VFRValue scaled(sead::Mathf::abs(input));
        scaled.updateStats();
        polar._8 = angleStuff(polar._8 + sub_7100924DFC(sign * scaled.mean));
        auto* current_player = sub_7100926A14();
        if (!current_player)
            return;
        if (sub_7100926D24() && !current_player->x_48())
            polar._8 = angleStuff(polar._8 + yaw_delta);
        _154 = polar._8;
        _160 = 0;
        if (sub_7100925110(_74._0, 0))
            _160 = 0;
        else if (sub_7100925110(_74._0, 1))
            _160 = 1;
        else if (sub_7100925110(_74._0, 2))
            _160 = 2;
        _164 = 0.0f;
    }
    _1c8 = yaw;
    f32 radius = 0.0f;
    sub_710074D4A4(&radius);
    _4c += (radius - _4c) * *mRadiusCus_s;
    polar._0 = _4c + blend * _50;
    sub_710074D598(polar);
    const sead::Vector3f displacement = translation - sub_7100928868(camera->_860._164);
    const f32 inv_elapsed = 1.0f / elapsed;
    const f32 horizontal_speed = inv_elapsed * std::sqrt(
        displacement.x * displacement.x + displacement.z * displacement.z);
    const sead::Vector3f previous_displacement = sub_7100928868(camera->_860._174);
    const f32 horizontal_acceleration = inv_elapsed * std::sqrt(
        sead::Mathf::square(displacement.x - previous_displacement.x) +
        sead::Mathf::square(displacement.z - previous_displacement.z));
    const f32 acceleration_rate = 0.1f + std::min(sead::Mathf::abs(horizontal_acceleration), 0.05f) /
                                           0.05f * 0.8f;
    const f32 motion_rate = sub_7100791E44(0.9f);
    _19c += motion_rate * (acceleration_rate - _19c);
    const f32 horizontal_phase = std::min(sead::Mathf::abs(horizontal_speed), 0.5f) *
                                 2.0f * sead::Mathf::pi() - sead::Mathf::pi() * 0.5f;
    const f32 horizontal_response = _188 + (std::sin(horizontal_phase) + 1.0f) * 0.5f * (_18c - _188);
    const f32 horizontal_rate = sub_7100791E44(_19c);
    _198 += horizontal_rate * (horizontal_response - _198);
    const f32 horizontal_smoothing = sub_7100791E44(_198);
    const f32 vertical_speed = inv_elapsed * sead::Mathf::abs(displacement.y);
    const f32 vertical_acceleration = inv_elapsed * sead::Mathf::abs(
        displacement.y - sub_7100928868(camera->_860._174).y);
    const f32 vertical_acceleration_rate = 0.1f +
        std::min(sead::Mathf::abs(vertical_acceleration), 0.05f) / 0.05f * 0.8f;
    const f32 vertical_motion_rate = sub_7100791E44(0.9f);
    _1a4 += vertical_motion_rate * (vertical_acceleration_rate - _1a4);
    const f32 vertical_phase = std::min(sead::Mathf::abs(vertical_speed), 1.0f) *
                               sead::Mathf::pi() - sead::Mathf::pi() * 0.5f;
    const f32 vertical_response = _190 + (std::sin(vertical_phase) + 1.0f) * 0.5f * (_194 - _190);
    const f32 vertical_rate = sub_7100791E44(_1a4);
    _1a0 += vertical_rate * (vertical_response - _1a0);
    const f32 vertical_smoothing = sub_7100791E44(_1a0);
    _54.x += horizontal_smoothing * (_170.x - _54.x);
    _54.y += vertical_smoothing * (_170.y - _54.y);
    _54.z += horizontal_smoothing * (_170.z - _54.z);
    _54.y = sead::Mathf::clamp(_54.y, _170.y - 0.5f, _170.y + 0.5f);
    camera->_860._0._c = _54 + _60 * blend;
    camera->_860._0._0 = camera->_860._0._c + polar.sub_7100923254();
    camera->_860._0._24 = _6c + blend * _70;
    _28a = _289;
    camera->_860.sub_710079BD5C();
    camera->sub_71007953C8();
}

// NON_MATCHING: polar and displacement value lifetimes differ.
void CameraAiming::sub_710074C97C() {
    auto* camera = getCamera();
    if (!camera)
        return;
    const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    _150 = angleStuff(sead::Mathf::clamp(angleStuff(polar._4 + *mLatOffset_s), _280, _284));
    _158 = _150;
    _15c = angleStuff(polar._4 - _150);
    _154 = polar._8;
    f32 radius = 0.0f;
    sub_710074D4A4(&radius);
    _4c = radius;
    _50 = (camera->_860._0._c - camera->_860._0._0).length() - _4c;
    const sead::Vector3f translation = camera->_860._270.getTranslation();
    const sead::Vector3f displacement = translation - sub_7100928868(camera->_860._164);
    _54 = _170 - displacement;
    _60 = (displacement + camera->_860._0._c) - _170;
    _6c = sead::Mathf::deg2rad(*mFovy_s);
    _70 = camera->_860._0._24 - _6c;
    _288 = u32(*mConnectType_s) < 2 ? *mConnectType_s : 0;
    sub_710074D9EC();
}

void CameraAiming::sub_710074D4A4(f32* out) {
    auto* camera = getCamera();
    if (!camera)
        return;

    const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    f32 rate = 0.0f;
    if (*mRadiusMinLat_s != *mRadiusMaxLat_s) {
        rate = angleStuff(angleStuff(polar._4 - *mRadiusMinLat_s) /
                          (*mRadiusMaxLat_s - *mRadiusMinLat_s));
        rate = sead::Mathf::clamp(rate, 0.0f, 1.0f);
    }
    *out = *mRadiusMin_s + rate * (*mRadiusMax_s - *mRadiusMin_s);
}

void CameraAiming::m35() {
    if (auto* camera = getCamera())
        camera->_860._7f8.reset(1);
}

void CameraAiming::m36() {
    getStaticParam(&mLatMin_s, "latMin");
    getStaticParam(&mLatMax_s, "latMax");
    getStaticParam(&mLatOffset_s, "LatOffset");
    getStaticParam(&mLatStickScale_s, "latStickScale");
    getStaticParam(&mLngStickScale_s, "lngStickScale");
    getStaticParam(&mLatGyroScale_s, "latGyroScale");
    getStaticParam(&mLngGyroScale_s, "lngGyroScale");
    getStaticParam(&mRadiusMin_s, "radiusMin");
    getStaticParam(&mRadiusMax_s, "radiusMax");
    getStaticParam(&mRadiusMinLat_s, "radiusMinLat");
    getStaticParam(&mRadiusMaxLat_s, "radiusMaxLat");
    getStaticParam(&mRadiusCus_s, "radiusCus");
    getStaticParam(&mSideOffset_s, "sideOffset");
    getStaticParam(&mWorldBaseOffset_s, "worldBaseOffset");
    getStaticParam(&mOffsetZ_s, "OffsetZ");
    getStaticParam(&mOffsetZMin_s, "OffsetZMin");
    getStaticParam(&mOffsetZMax_s, "OffsetZMax");
    getStaticParam(&mAtCus_s, "atCus");
    getStaticParam(&mFovy_s, "fovy");
    getStaticParam(&mGyro_s, "gyro");
    getStaticParam(&mConnectType_s, "ConnectType");
    getStaticParam(&mConnect_s, "Connect");
}

void CameraAiming::sub_710074D598(const act::Unk_7100922700& polar) {
    sead::Matrix34f transform = sead::Matrix34f::ident;
    sub_710074DAE8(&transform);
    sead::Vector3f target = sead::Vector3f::zero;
    sub_710074DBD0(transform, &target);
    const f32 rate = sub_7100791E44(0.1f);
    _17c += (target - _17c) * rate;
    _170.setMul(transform, _17c);
    sead::Vector3f offset = sead::Vector3f::zero;
    sub_710074DD28(polar, &offset);
    _170 += offset;
}

void CameraAiming::sub_710074D9EC() {
    if (_288 == 1) {
        _1a8.sub_710079C384(sub_7100924F04(), 0.0f);
        return;
    }

    f32 frames = 0.0f;
    if (_50 != 0.0f)
        frames = sead::Mathf::max(sead::Mathf::abs(_50) * 0.5f, 0.0f);
    const sead::Vector3f offset = _60;
    if (offset != sead::Vector3f(0, 0, 0)) {
        const f32 length = offset.length();
        if (frames < length)
            frames = length;
    }
    if (_70 != 0.0f) {
        const f32 fovy = sead::Mathf::abs(_70) * 30.0f;
        if (frames < fovy)
            frames = fovy;
    }
    if (frames > 0.0f && frames < 5.0f)
        frames = 5.0f;
    _1a8.sub_710079C384(frames, 0.0f);
}

void CameraAiming::sub_710074DAE8(sead::Matrix34f* mtx) {
    auto* camera = getCameraActor();
    if (!camera)
        return;

    ksys::act::acc::PlayerBase player;
    sub_7100926A50(&player);
    if (!player.hasProc())
        return;

    if (sub_7100926D24()) {
        ksys::act::ActorConstDataAccess horse;
        sub_7100926A74(&horse);
        if (horse.hasProc())
            *mtx = horse.getActorMtx();
    } else if (player.m193()) {
        ksys::act::ActorConstDataAccess parent;
        player.acquireConnectedCalcParent(&parent);
        *mtx = parent.getActorMtx();
    } else {
        *mtx = camera->_860._270;
    }
}

void CameraAiming::sub_710074DBD0(const sead::Matrix34f& mtx, sead::Vector3f* out) {
    out->set(0.0f, 0.0f, 0.0f);
    if (sub_7100926D24()) {
        if (!_28b)
            return;
    } else {
        ksys::act::acc::PlayerBase player;
        sub_7100926A50(&player);
        if (!player.hasProc())
            return;
        if (player.m193())
            return;
    }

    auto* camera = getCameraActor();
    if (!camera)
        return;

    *out = camera->_860._2b8;
    sead::Matrix34f inv = sead::Matrix34f::ident;
    inv.setInverse(mtx);
    out->setMul(inv, *out);
}

// NON_MATCHING: yaw rotation specialization and vector scheduling differ for non-finite input.
void CameraAiming::sub_710074DD28(const act::Unk_7100922700& polar, sead::Vector3f* out) {
    *out = sead::Vector3f::zero;
    auto* camera = getCameraActor();
    if (!camera)
        return;
    *out += *mWorldBaseOffset_s;
    const sead::Vector3f direction = camera->_860._0._c - camera->_860._0._0;
    sead::Vector3f side_offset = sead::Vector3f::zero;
    const f32 side = -*mSideOffset_s;
    sub_7100924E48(direction, side, &side_offset);
    *out += side_offset;
    {
        ksys::act::ActorConstDataAccess target;
        sub_710074E3EC(&target);
        const auto& transform = target.getActorMtx();
        const f32 yaw = sead::Mathf::deg2rad(angleStuff(polar._8 + 180.0f)) -
                        std::atan2(transform(0, 2), transform(2, 2));
        const f32 sine = std::sin(yaw);
        const f32 cosine = std::cos(yaw);
        sead::Vector3f forward = sead::Vector3f::ez * *mOffsetZ_s;
        forward.set(forward.x * cosine + forward.z * sine, forward.y,
                    forward.z * cosine - forward.x * sine);
        forward.rotate(transform);
        *out += forward;
    }
    const f32 latitude_rate = angleStuff(angleStuff(polar._4 + 90.0f) / 180.0f);
    const f32 offset_length = *mOffsetZMin_s + latitude_rate * (*mOffsetZMax_s - *mOffsetZMin_s);
    const sead::Vector3f polar_offset = polar.sub_7100923254();
    sead::Vector3f horizontal(polar_offset.x, 0.0f, polar_offset.z);
    const f32 length = horizontal.length();
    if (length > 0.0f)
        horizontal *= offset_length / length;
    *out -= horizontal;
    if (sub_7100926D24()) {
        ksys::act::acc::PlayerBase player;
        sub_7100926A50(&player);
        if (player.hasProc() && !_28b) {
            ksys::act::ActorConstDataAccess mount;
            sub_7100926A74(&mount);
            if (mount.hasProc()) {
                if (sub_7100926DF0(mount) || sub_7100926E7C(mount))
                    out->y += sub_71009221D4();
                else if (mount.hasTag(0xFFB635E5))
                    out->y += sub_71009221DC();
            }
        }
    }
    auto* player = sub_7100926A14();
    if (!player || !player->x_48())
        return;
    auto* actor = sead::DynamicCast<ksys::act::Actor>(
        ksys::act::PlayerInfo::instance()->getHorseLink().getProc(nullptr, nullptr));
    auto* motorcycle = sead::DynamicCast<act::Motorcycle>(actor);
    if (!motorcycle)
        return;
    const sead::Matrix34f transform = motorcycle->getMainBody()->getTransform();
    const f32 weight = sub_7100922418();
    sead::Vector3f vertical_offset;
    vertical_offset.setRotated(transform, sead::Vector3f::ey * weight);
    sead::Vector3f axis(transform(0, 0), 0.0f, transform(2, 0));
    const f32 axis_length = axis.length();
    if (axis_length > 0.0f)
        axis *= 1.0f / axis_length;
    sead::Vector3f tilt;
    tilt.setCross(transform.getBase(2), sead::Vector3f::ey);
    const f32 tilt_length = tilt.length();
    f32 factor = 0.0f;
    if (!(tilt_length < 0.0f)) {
        const f32 clamped = sead::Mathf::clampMax(tilt_length, 1.0f);
        if (clamped != 0.0f)
            factor = sead::Mathf::expTable(sead::Mathf::logTable(clamped) * 4.0f);
    }
    *out += (axis * axis.dot(vertical_offset)) * factor;
}

// NON_MATCHING: the original shares one acquireActor call (and one accessor destructor) between the
// horse and connected-parent paths
void CameraAiming::sub_710074E3EC(ksys::act::ActorConstDataAccess* accessor) {
    ksys::act::acc::PlayerBase player;
    sub_7100926A50(&player);
    if (!player.hasProc())
        return;

    if (sub_7100926D24()) {
        ksys::act::ActorConstDataAccess horse;
        sub_7100926A9C(&horse);
        if (horse.hasProc())
            accessor->acquireActor(horse);
        else
            accessor->acquireActor(player);
    } else if (player.m193()) {
        ksys::act::ActorConstDataAccess parent;
        player.acquireConnectedCalcParent(&parent);
        if (parent.hasProc())
            accessor->acquireActor(parent);
        else
            accessor->acquireActor(player);
    } else {
        accessor->acquireActor(player);
    }
}

}  // namespace uking::action
