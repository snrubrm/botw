#include "Game/AI/Action/actionCameraAiming2.h"
#include <math/seadMathCalcCommon.h>
#include <cmath>
#include <algorithm>
#include "KingSystem/System/Timer.h"
#include "KingSystem/System/VFRValue.h"
#include "Game/Framework/gameSystemStruct1.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

CameraAiming2::CameraAiming2(const InitArg& arg) : CameraAction(arg) {}

CameraAiming2::~CameraAiming2() = default;

// NON_MATCHING: the original evaluates the clamps branch-free (fcsel / fccmp)
void CameraAiming2::sub_710074EC10() {
    sub_7100924CDC(*mLatMin_s, *mLatMax_s, &_278, &_27c);
    _280 = sead::Mathf::clamp(*mLatMinWidth_s, 0.0f, 0.5f);
    _284 = sead::Mathf::clamp(*mLatMaxWidth_s, 0.0f, 0.5f);
    _288 = sub_7100924D40(*mRadiusMin_s);
    _28c = sub_7100924D40(*mRadiusMax_s);
    _290 = sead::Mathf::clamp(*mRadiusMinWidth_s, 0.0f, 0.5f);
    _294 = sead::Mathf::clamp(*mRadiusMaxWidth_s, 0.0f, 0.5f);
    _298 = sead::Mathf::clamp(*mOffsetYMinWidth_s, 0.0f, 0.5f);
    _29c = sead::Mathf::clamp(*mOffsetYMaxWidth_s, 0.0f, 0.5f);
    _2a0 = sub_7100924D50(*mFovy_s);
    const u32 gyro = *mGyro_s;
    _2a4 = gyro > 2 ? 0 : gyro;
}

// NON_MATCHING: accessor lifetime, motion snapshots and float scheduling differ.
void CameraAiming2::m33() {
    sub_710074EC10();
    sub_710074ED54();
    _7c.sub_71008A4644();
    _2a8 = 2;
    ksys::act::acc::PlayerBase player;
    sub_7100926A50(&player);
    if (!player.hasProc())
        return;
    ksys::act::ActorConstDataAccess target;
    if (sub_7100926D24()) {
        sub_7100926A9C(&target);
    } else if (player.m193()) {
        player.acquireConnectedCalcParent(&target);
    } else {
        target.acquireActor(player);
    }
    if (!target.hasProc())
        return;
    const sead::Matrix34f& transform = target.getActorMtx();
    f32 yaw = 0.0f;
    if (transform(0, 2) != 0.0f || transform(2, 2) != 0.0f)
        yaw = sead::Mathf::rad2deg(std::atan2(transform(0, 2), transform(2, 2)));
    _1a0 = angleStuff(yaw);
    auto* camera = getCamera();
    if (!camera)
        return;
    const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    _158 = _4c;
    _15c = polar._8;
    f32 elapsed = 0.0f;
    ksys::Timer::update(&elapsed, 1.0f);
    if (elapsed == 0.0f)
        return;
    sead::Vector3f translation;
    camera->_860._270.getTranslation(translation);
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
    _170 = _160 + horizontal_blend * (_164 - _160);
    _174 = 0.1f + std::min(sead::Mathf::abs(horizontal_acceleration), 0.05f) / 0.05f *
                        (0.9f - 0.1f);
    const f32 vertical_acceleration = inv_elapsed * sead::Mathf::abs(
        displacement.y - sub_7100928868(camera->_860._174).y);
    const f32 vertical_speed = inv_elapsed * sead::Mathf::abs(displacement.y);
    const f32 vertical_phase = std::min(sead::Mathf::abs(vertical_speed), 1.0f) *
                               sead::Mathf::pi() - sead::Mathf::pi() * 0.5f;
    const f32 vertical_blend = (std::sin(vertical_phase) + 1.0f) * 0.5f;
    _178 = _168 + vertical_blend * (_16c - _168);
    _17c = 0.1f + std::min(sead::Mathf::abs(vertical_acceleration), 0.05f) / 0.05f *
                        (0.9f - 0.1f);
    if (camera->_860._7fc.sub_710079C0CC(0x100000)) {
        _180.sub_710079C510(1.0f);
        camera->_860._0._c = _5c;
        const act::Unk_7100922700 direction(_54, _4c, _15c);
        camera->_860._0._0 = camera->_860._0._c + direction.sub_7100923254();
        camera->_860._0._24 = _74;
        camera->_860._0._28 = 0.0f;
    }
}

// NON_MATCHING: accessor paths, curve lifetimes and motion/angle scheduling differ.
void CameraAiming2::m34() {
    sub_710074EC10();
    auto* camera = getCamera();
    if (!camera)
        return;
    const act::Unk_7100922700 initial(camera->_860._0._0 - camera->_860._0._c);
    act::Unk_7100922700 polar = initial;
    ksys::act::acc::PlayerBase player;
    sub_7100924BE4(&player);
    if (!player.hasProc())
        return;
    ksys::act::ActorConstDataAccess target;
    target.acquireActor(player);
    if (sub_7100926D24()) {
        ksys::act::ActorConstDataAccess horse;
        sub_7100926A9C(&horse);
        if (horse.hasProc())
            target.acquireActor(horse);
    } else if (player.m193()) {
        ksys::act::ActorConstDataAccess parent;
        player.acquireConnectedCalcParent(&parent);
        // Native 74F2CC / 74F2E0 repeat the acquisition after checking the first result.
        if (parent.hasProc())
            player.acquireConnectedCalcParent(&parent);
    }
    const sead::Matrix34f& transform = target.getActorMtx();
    if (ksys::util::sub_71011F10F4(transform))
        return;
    sead::Vector3f translation;
    camera->_860._270.getTranslation(translation);
    f32 elapsed = 0.0f;
    ksys::Timer::update(&elapsed, 1.0f);
    if (elapsed == 0.0f)
        return;
    sead::Vector2f stick = sead::Vector2f::zero;
    sub_7100924F08(&stick);
    sead::Matrix33f gyro_matrix = sead::Matrix33f::ident;
    if (stick.x == 0.0f && stick.y == 0.0f && _2a4 != 1 &&
        (_2a4 != 2 || sub_710092732C())) {
        _2a8 = 1;
        _7c.sub_71008A4694(0.0f);
        gyro_matrix = _7c._0;
        // Native relative-matrix call is retained although this caller does not read its output.
        sub_71009238F8(&gyro_matrix, _7c._b4);
    } else {
        _2a8 = 0;
        _158 = _4c;
        _7c.sub_71008A4644();
    }
    f32 latitude_t = 0.0f;
    f32 radius_t = 0.0f;
    f32 input = 0.0f;
    if (_278 != _27c) {
        f32 latitude_input = 0.0f;
        if (_2a8 != 0) {
            if (auto* controller = frm::SystemStruct1::getInstance())
                latitude_input = controller->_8.x * 360.0f / 30.0f * *mLatGyroScale_s;
        } else {
            latitude_input = stick.y * sub_7100927228() * sub_7100927238() * *mLatStickScale_s;
        }
        input = latitude_input / sead::Mathf::abs(_27c - _278);
        const f32 latitude = sead::Mathf::clamp(_158, _278, _27c);
        act::Unk_71024741b8 latitude_curve;
        latitude_curve.set(_278, _278, _27c, _27c, *mLatMinWeight_s, *mLatMaxWeight_s);
        latitude_t = latitude_curve.sub_71009234D8(latitude, 10);
        act::Unk_71024741b8 rate_curve;
        rate_curve.set(0.0f, _280, 1.0f - _284, 1.0f, *mLatMinWeight_s, *mLatMaxWeight_s);
        latitude_t = rate_curve.eval(latitude_t);
    }
    if (_288 != _28c) {
        f32 min = 0.0f;
        f32 max = 0.0f;
        sub_7100924C94(_288, _28c, &min, &max);
        const f32 radius = sead::Mathf::clamp(_54, min, max);
        act::Unk_71024741b8 radius_curve;
        radius_curve.set(_288, _288, _28c, _28c, *mRadiusMinWeight_s, *mRadiusMaxWeight_s);
        radius_t = radius_curve.sub_71009234D8(radius, 10);
        act::Unk_71024741b8 rate_curve;
        rate_curve.set(0.0f, _290, 1.0f - _294, 1.0f, *mRadiusMinWeight_s, *mRadiusMaxWeight_s);
        radius_t = rate_curve.eval(radius_t);
    }
    if (_278 != _27c) {
        if (_288 == _28c) {
            latitude_t = 0.0f;
        } else {
            const f32 direction = input > 0.0f ? 1.0f : -1.0f;
            const f32 latitude_distance = direction - latitude_t;
            const f32 radius_distance = direction - radius_t;
            const bool latitude_first = sead::Mathf::abs(radius_distance) <
                                        sead::Mathf::abs(latitude_distance);
            f32& first = latitude_first ? latitude_t : radius_t;
            f32& second = latitude_first ? radius_t : latitude_t;
            const f32 first_distance = latitude_first ? latitude_distance : radius_distance;
            const f32 second_distance = latitude_first ? radius_distance : latitude_distance;
            const f32 previous = first;
            first = sead::Mathf::clamp(first + input, -1.0f, 1.0f);
            const f32 proportion = first_distance != 0.0f ? (first - previous) / first_distance : 1.0f;
            second = sead::Mathf::clamp(second + second_distance * proportion, -1.0f, 1.0f);
        }
    }
    _180.sub_710079C3F8(sead::Mathf::clampMin(*mConnect_s, 0.0f));
    _180.sub_710079C408();
    const f32 blend = 1.0f - _180._18;
    {
        act::Unk_71024741b8 rate_curve;
        rate_curve.set(0.0f, _280, 1.0f - _284, 1.0f, *mLatMinWeight_s, *mLatMaxWeight_s);
        latitude_t = rate_curve.sub_71009234D8(latitude_t, 10);
        act::Unk_71024741b8 latitude_curve;
        latitude_curve.set(_278, _278, _27c, _27c, *mLatMinWeight_s, *mLatMaxWeight_s);
        _158 = angleStuff(latitude_curve.eval(latitude_t));
    }
    const f32 latitude_rate = sub_7100791E44(_2a8 == 1 ? 0.5f : 1.0f);
    _4c = angleStuff(angleStuff(latitude_rate * angleStuff(_158 - _4c)) + _4c);
    polar._4 = angleStuff(sub_7100924CAC(angleStuff(angleStuff(blend * _50) + _4c)));
    f32 yaw = angleStuff(0.0f);
    if (transform(0, 2) != 0.0f || transform(2, 2) != 0.0f)
        yaw = angleStuff(sead::Mathf::rad2deg(std::atan2(transform(0, 2), transform(2, 2))));
    const f32 yaw_delta = angleStuff(yaw - _1a0);
    if (_2a8 == 1) {
        const f32 gyro = sub_7100923E2C();
        _15c = angleStuff(_15c + gyro * *mLngGyroScale_s);
        const f32 longitude_rate = sub_7100791E44(0.5f);
        polar._8 = angleStuff(angleStuff(longitude_rate * angleStuff(_15c - initial._8)) + initial._8);
    } else {
        const f32 longitude_scale = sub_7100927230() * sub_71009272A8();
        const f32 longitude_input = longitude_scale * *mLngStickScale_s * stick.x;
        const f32 magnitude = sead::Mathf::abs(longitude_input);
        const f32 sign = longitude_input > 0.0f ? 1.0f : -1.0f;
        ksys::VFRValue value(magnitude);
        value.updateStats();
        polar._8 = angleStuff(polar._8 + sub_7100924DFC(sign * value.mean));
        if (sub_7100926D24())
            polar._8 = angleStuff(yaw_delta + polar._8);
        _15c = polar._8;
    }
    _1a0 = yaw;
    const f32 inv_elapsed = 1.0f / elapsed;
    f32 radius;
    {
        act::Unk_71024741b8 rate_curve;
        rate_curve.set(0.0f, _290, 1.0f - _294, 1.0f, *mRadiusMinWeight_s, *mRadiusMaxWeight_s);
        radius_t = rate_curve.sub_71009234D8(radius_t, 10);
        act::Unk_71024741b8 radius_curve;
        radius_curve.set(_288, _288, _28c, _28c, *mRadiusMinWeight_s, *mRadiusMaxWeight_s);
        radius = radius_curve.eval(radius_t);
    }
    const f32 radius_rate = sub_7100791E44(_2a8 == 1 ? 0.5f : 1.0f);
    _54 += radius_rate * (radius - _54);
    polar._0 = sub_7100924D40(_54 + blend * _58);
    sead::Vector3f next_target = sead::Vector3f::zero;
    sub_710074FDF0(&next_target);
    const sead::Vector3f displacement = translation - sub_7100928868(camera->_860._164);
    const f32 horizontal_speed = inv_elapsed * std::sqrt(
        displacement.x * displacement.x + displacement.z * displacement.z);
    const sead::Vector3f previous_displacement = sub_7100928868(camera->_860._174);
    const f32 horizontal_acceleration = inv_elapsed * std::sqrt(
        sead::Mathf::square(displacement.x - previous_displacement.x) +
        sead::Mathf::square(displacement.z - previous_displacement.z));
    const f32 acceleration_rate = 0.1f + std::min(sead::Mathf::abs(horizontal_acceleration), 0.05f) /
                                           0.05f * (0.9f - 0.1f);
    const f32 motion_rate = sub_7100791E44(0.9f);
    _174 += motion_rate * (acceleration_rate - _174);
    const f32 horizontal_phase = std::min(sead::Mathf::abs(horizontal_speed), 0.5f) *
                                 2.0f * sead::Mathf::pi() - sead::Mathf::pi() * 0.5f;
    const f32 horizontal_blend = (std::sin(horizontal_phase) + 1.0f) * 0.5f;
    const f32 horizontal_response = _160 + horizontal_blend * (_164 - _160);
    const f32 horizontal_rate = sub_7100791E44(_174);
    _170 += horizontal_rate * (horizontal_response - _170);
    const f32 horizontal_smoothing = sub_7100791E44(_170);
    const f32 vertical_acceleration = inv_elapsed * sead::Mathf::abs(
        displacement.y - sub_7100928868(camera->_860._174).y);
    const f32 vertical_speed = inv_elapsed * sead::Mathf::abs(displacement.y);
    const f32 vertical_acceleration_rate = 0.1f +
        std::min(sead::Mathf::abs(vertical_acceleration), 0.05f) / 0.05f * (0.9f - 0.1f);
    const f32 vertical_motion_rate = sub_7100791E44(0.9f);
    _17c += vertical_motion_rate * (vertical_acceleration_rate - _17c);
    const f32 vertical_phase = std::min(sead::Mathf::abs(vertical_speed), 1.0f) *
                               sead::Mathf::pi() - sead::Mathf::pi() * 0.5f;
    const f32 vertical_blend = (std::sin(vertical_phase) + 1.0f) * 0.5f;
    const f32 vertical_response = _168 + vertical_blend * (_16c - _168);
    const f32 vertical_rate = sub_7100791E44(_17c);
    _178 += vertical_rate * (vertical_response - _178);
    const f32 vertical_smoothing = sub_7100791E44(_178);
    _5c.x += horizontal_smoothing * (next_target.x - _5c.x);
    _5c.y += vertical_smoothing * (next_target.y - _5c.y);
    _5c.z += horizontal_smoothing * (next_target.z - _5c.z);
    const f32 vertical_offset = _5c.y - next_target.y;
    if (vertical_offset > 0.5f)
        _5c.y = next_target.y + 0.5f;
    else if (vertical_offset < -0.5f)
        _5c.y = next_target.y - 0.5f;
    camera->_860._0._c = _5c + _68 * blend;
    camera->_860._0._0 = camera->_860._0._c + polar.sub_7100923254();
    camera->_860._0._24 = _74 + blend * _78;
    camera->_860.sub_710079BD5C();
    camera->sub_71007953C8();
}

// NON_MATCHING: curve lifetime, vector copying and radius scheduling differ.
void CameraAiming2::sub_710074ED54() {
    auto* camera = getCamera();
    if (!camera)
        return;
    const act::Unk_7100922700 initial(camera->_860._0._0 - camera->_860._0._c);
    _4c = angleStuff(sead::Mathf::clamp(initial._4, _278, _27c));
    _50 = angleStuff(initial._4 - _4c);
    f32 radius;
    f32 t;
    {
        act::Unk_71024741b8 latitude_curve;
        latitude_curve.set(_278, _278, _27c, _27c, *mLatMinWeight_s, *mLatMaxWeight_s);
        t = latitude_curve.sub_71009234D8(_4c, 10);
        act::Unk_71024741b8 rate_curve;
        rate_curve.set(0.0f, _280, 1.0f - _284, 1.0f, *mLatMinWeight_s, *mLatMaxWeight_s);
        t = rate_curve.eval(t);
    }
    {
        act::Unk_71024741b8 rate_curve;
        rate_curve.set(0.0f, _290, 1.0f - _294, 1.0f, *mRadiusMinWeight_s, *mRadiusMaxWeight_s);
        t = rate_curve.sub_71009234D8(t, 10);
        act::Unk_71024741b8 radius_curve;
        radius_curve.set(_288, _288, _28c, _28c, *mRadiusMinWeight_s, *mRadiusMaxWeight_s);
        radius = radius_curve.eval(t);
    }
    const f32 tolerance = sub_7100922378();
    if (!(tolerance < sead::Mathf::abs(initial._0 - radius))) {
        f32 min = 0.0f;
        f32 max = 0.0f;
        sub_7100924C94(_288, _28c, &min, &max);
        radius = sead::Mathf::clamp(initial._0, min, max);
    }
    _54 = radius;
    _58 = initial._0 - radius;
    sead::Vector3f target = sead::Vector3f::zero;
    sub_710074FDF0(&target);
    _5c = target;
    _68 = camera->_860._0._c - target;
    sead::Vector3f translation;
    camera->_860._270.getTranslation(translation);
    const sead::Vector3f delta = translation - sub_7100928868(camera->_860._164);
    sead::Vector3f projection = sead::Vector3f::zero;
    ksys::util::sub_71011EFA54(&projection, delta, _68);
    if (_68.dot(projection) > 0.0f)
        projection.set(0.0f, 0.0f, 0.0f);
    if (_68.dot(_68 + projection) < 0.0f)
        projection = -_68;
    _5c -= projection;
    _68 += projection;
    _74 = _2a0;
    _78 = camera->_860._0._24 - _74;
    f32 amount = 0.0f;
    if (_58 != 0.0f)
        amount = std::fmax(sead::Mathf::abs(_58) * 0.5f, 0.0f);
    if (_68.x != 0.0f || _68.y != 0.0f || _68.z != 0.0f) {
        const f32 distance = _68.length();
        amount = amount < distance ? distance : amount;
    }
    if (_78 != 0.0f) {
        const f32 fovy = sead::Mathf::abs(_78) * 10.0f;
        amount = amount < fovy ? fovy : amount;
    }
    if (amount > 0.0f && amount < 5.0f)
        amount = 5.0f;
    _180.sub_710079C384(amount, 0.0f);
}

// NON_MATCHING: the height output occupies a different stack slot.
void CameraAiming2::sub_710074FDF0(sead::Vector3f* out) {
    auto* camera = getCamera();
    if (!camera)
        return;
    *out = camera->_860._2b8;
    if (sub_7100926D24()) {
        if (auto* actor = sead::DynamicCast<ksys::act::Actor>(
                ksys::act::PlayerInfo::instance()->getHorseLink().getProc(nullptr, nullptr)))
            actor->getMtx().getTranslation(*out);
    } else {
        ksys::act::acc::PlayerBase player;
        sub_7100926A50(&player);
        if (player.m193()) {
            ksys::act::ActorConstDataAccess parent;
            player.acquireConnectedCalcParent(&parent);
            parent.getActorMtx().getTranslation(*out);
        }
    }
    const sead::Vector3f direction = camera->_860._0._c - camera->_860._0._0;
    sead::Vector3f offset = sead::Vector3f::zero;
    const f32 side = -*mSideOffset_s;
    sub_7100924E48(direction, side, &offset);
    *out += offset;
    f32 height = 0.0f;
    sub_7100750334(&height);
    out->y += height;
}

void CameraAiming2::m35() {
    if (auto* camera = getCamera())
        camera->_860._7f8.reset(1);
}

void CameraAiming2::m36() {
    getStaticParam(&mLatMin_s, "LatMin");
    getStaticParam(&mLatMax_s, "LatMax");
    getStaticParam(&mLatMinWidth_s, "LatMinWidth");
    getStaticParam(&mLatMaxWidth_s, "LatMaxWidth");
    getStaticParam(&mLatMinWeight_s, "LatMinWeight");
    getStaticParam(&mLatMaxWeight_s, "LatMaxWeight");
    getStaticParam(&mLatStickScale_s, "LatStickScale");
    getStaticParam(&mLngStickScale_s, "LngStickScale");
    getStaticParam(&mLatGyroScale_s, "LatGyroScale");
    getStaticParam(&mLngGyroScale_s, "LngGyroScale");
    getStaticParam(&mRadiusMin_s, "RadiusMin");
    getStaticParam(&mRadiusMax_s, "RadiusMax");
    getStaticParam(&mRadiusMinWidth_s, "RadiusMinWidth");
    getStaticParam(&mRadiusMaxWidth_s, "RadiusMaxWidth");
    getStaticParam(&mRadiusMinWeight_s, "RadiusMinWeight");
    getStaticParam(&mRadiusMaxWeight_s, "RadiusMaxWeight");
    getStaticParam(&mSideOffset_s, "SideOffset");
    getStaticParam(&mOffsetYMin_s, "OffsetYMin");
    getStaticParam(&mOffsetYMax_s, "OffsetYMax");
    getStaticParam(&mOffsetYMinWidth_s, "OffsetYMinWidth");
    getStaticParam(&mOffsetYMaxWidth_s, "OffsetYMaxWidth");
    getStaticParam(&mOffsetYMinWeight_s, "OffsetYMinWeight");
    getStaticParam(&mOffsetYMaxWeight_s, "OffsetYMaxWeight");
    getStaticParam(&mFovy_s, "Fovy");
    getStaticParam(&mGyro_s, "Gyro");
    getStaticParam(&mConnect_s, "Connect");
}

void CameraAiming2::sub_7100750334(f32* out) {
    f32 offset = *mOffsetYMin_s;
    if (_278 != _27c || *mOffsetYMin_s == *mOffsetYMax_s) {
        if (*mOffsetYMin_s != *mOffsetYMax_s) {
            const f32 lat = _4c;
            f32 t;
            {
                act::Unk_71024741b8 curve;
                curve.set(_278, _278, _27c, _27c, *mLatMinWeight_s, *mLatMaxWeight_s);
                t = curve.sub_71009234D8(lat, 10);
                act::Unk_71024741b8 rate_curve;
                rate_curve.set(0.0f, _280, 1.0f - _284, 1.0f, *mLatMinWeight_s, *mLatMaxWeight_s);
                t = rate_curve.eval(t);
            }
            {
                act::Unk_71024741b8 rate_curve;
                rate_curve.set(0.0f, _298, 1.0f - _29c, 1.0f, *mOffsetYMaxWeight_s,
                               *mOffsetYMinWeight_s);
                t = rate_curve.sub_71009234D8(t, 10);
                act::Unk_71024741b8 curve;
                curve.set(*mOffsetYMax_s, *mOffsetYMax_s, *mOffsetYMin_s, *mOffsetYMin_s,
                          *mOffsetYMaxWeight_s, *mOffsetYMinWeight_s);
                offset = curve.eval(t);
            }
        }
    } else {
        offset = (*mOffsetYMin_s + *mOffsetYMax_s) * 0.5f;
    }
    *out = offset;
}

}  // namespace uking::action
