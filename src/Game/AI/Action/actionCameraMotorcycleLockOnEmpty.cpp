#include "Game/AI/Action/actionCameraMotorcycleLockOnEmpty.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actMotorcycle.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

CameraMotorcycleLockOnEmpty::CameraMotorcycleLockOnEmpty(const InitArg& arg) : CameraAction(arg) {}

CameraMotorcycleLockOnEmpty::~CameraMotorcycleLockOnEmpty() = default;

// NON_MATCHING: bound loads and scalar scheduling differ.
void CameraMotorcycleLockOnEmpty::sub_710077B7DC() {
    ksys::act::ActorConstDataAccess actor;
    sub_7100926A9C(&actor);
    if (actor.hasProc()) {
        const sead::Vector3f& velocity = actor.getVelocity();
        if (!ksys::util::sub_71011F1040(velocity)) {
            if (*mSpeedMin_s == *mSpeedMax_s) {
                _108 = 0.5f;
            } else {
                f32 min = 0.0f;
                f32 max = 0.0f;
                sub_7100924C94(*mSpeedMin_s, *mSpeedMax_s, &min, &max);
                f32 speed = velocity.length();
                if (speed < min)
                    speed = min;
                else if (speed > max)
                    speed = max;
                _108 = (speed - min) / (max - min);
            }
        }
    }
}

void CameraMotorcycleLockOnEmpty::m35() {
    if (auto* camera = getCamera())
        camera->_860._7f8.reset(1);
}

void CameraMotorcycleLockOnEmpty::m36() {
    getStaticParam(&mSpeedMax_s, "SpeedMax");
    getStaticParam(&mSpeedMin_s, "SpeedMin");
    getStaticParam(&mLatitudeMin_s, "LatitudeMin");
    getStaticParam(&mLatitudeMax_s, "LatitudeMax");
    getStaticParam(&mAutoLatitudeSlow_s, "AutoLatitudeSlow");
    getStaticParam(&mAutoLatitudeFast_s, "AutoLatitudeFast");
    getStaticParam(&mAutoLatitudeB2ICushion_s, "AutoLatitudeB2ICushion");
    getStaticParam(&mAutoLngBaseCushion_s, "AutoLngBaseCushion");
    getStaticParam(&mAutoLngMaxRotSpeed_s, "AutoLngMaxRotSpeed");
    getStaticParam(&mCameraRadiusSlow_s, "CameraRadiusSlow");
    getStaticParam(&mCameraRadiusFast_s, "CameraRadiusFast");
    getStaticParam(&mCameraRadiusB2ICushion_s, "CameraRadiusB2ICushion");
    getStaticParam(&mCameraFollowRotCushion_s, "CameraFollowRotCushion");
    getStaticParam(&mCameraFollowPosCushionX_s, "CameraFollowPosCushionX");
    getStaticParam(&mCameraFollowPosCushionYUp_s, "CameraFollowPosCushionYUp");
    getStaticParam(&mCameraFollowPosCushionYDown_s, "CameraFollowPosCushionYDown");
    getStaticParam(&mCameraFollowPosCushionZ_s, "CameraFollowPosCushionZ");
    getStaticParam(&mFovySlow_s, "FovySlow");
    getStaticParam(&mFovyFast_s, "FovyFast");
    getStaticParam(&mFovyBaseCushion_s, "FovyBaseCushion");
    getStaticParam(&mSwitchingCushionRate_s, "SwitchingCushionRate");
    getStaticParam(&mAtOffsetWorld_s, "AtOffsetWorld");
    getStaticParam(&mAtOffsetLocal_s, "AtOffsetLocal");
}

// NON_MATCHING: RTTI guards, transform/vector copies and scalar scheduling differ.
void CameraMotorcycleLockOnEmpty::m33() {
    auto* actor = sead::DynamicCast<act::Motorcycle>(sead::DynamicCast<ksys::act::Actor>(
        ksys::act::PlayerInfo::instance()->getHorseLink().getProc(nullptr, nullptr)));
    if (!actor)
        return;
    auto* camera = getCamera();
    if (!camera)
        return;
    _164 = true;
    sub_710077B7DC();
    const f32 latitude = angleStuff(sead::lerp(*mAutoLatitudeSlow_s, *mAutoLatitudeFast_s, _108));
    const sead::Matrix34f transform = actor->getMainBody()->getTransform();
    f32 yaw = angleStuff(0.0f);
    if (transform.m[0][2] != 0.0f || transform.m[2][2] != 0.0f)
        yaw = angleStuff(std::atan2(transform.m[0][2], transform.m[2][2]) * 57.295776f);
    yaw = angleStuff(sub_7100922530(yaw));
    const act::Unk_7100922700 current(camera->_860._0._0 - camera->_860._0._c);
    const act::Unk_7100922700 source(1.0f, current._4, current._8);
    const act::Unk_7100922700 target(1.0f, latitude, yaw);
    sub_710074BDF8(source.sub_7100923254().dot(target.sub_7100923254()));
}

void CameraMotorcycleLockOnEmpty::sub_710077BD98() {
    auto* actor = sead::DynamicCast<act::Motorcycle>(sead::DynamicCast<ksys::act::Actor>(
        ksys::act::PlayerInfo::instance()->getHorseLink().getProc(nullptr, nullptr)));
    if (actor)
        _168 = actor->getMainBody()->getTransform();
}

// NON_MATCHING: polar/vector copies and prepared-field loads differ.
void CameraMotorcycleLockOnEmpty::sub_710077C8A8() {
    auto* camera = getCamera();
    if (!camera)
        return;
    const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    _12c = _110;
    _148 = angleStuff(polar._4 - _110);
    _128 = _10c;
    _144 = angleStuff(polar._8 - _10c);
    _130 = _114;
    _134 = _118;
    _14c = polar._0 - _114;
    _150 = camera->_860._0._c - _118;
    _150 += camera->_860._0._c;
    _150 -= camera->_860._150;
    _140 = _124;
    _15c = camera->_860._0._24 - _124;
}

// NON_MATCHING: bound and prepared-field loads and scalar scheduling differ.
void CameraMotorcycleLockOnEmpty::sub_710077CC90() {
    auto* camera = getCamera();
    if (!camera)
        return;
    const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    _110 = angleStuff(sead::lerp(*mAutoLatitudeSlow_s, *mAutoLatitudeFast_s, _108));
    const sead::Vector3f position = camera->_860._0._c + polar.sub_7100923254();
    _110 = angleStuff(sub_710092738C(camera->_860._0._c, position) + _110);
    _110 = angleStuff(sead::Mathf::clamp(_110, *mLatitudeMin_s, *mLatitudeMax_s));
}

// NON_MATCHING: RTTI guards, transform/vector copies and scalar scheduling differ.
void CameraMotorcycleLockOnEmpty::sub_710077CDA4() {
    auto* actor = sead::DynamicCast<act::Motorcycle>(sead::DynamicCast<ksys::act::Actor>(
        ksys::act::PlayerInfo::instance()->getHorseLink().getProc(nullptr, nullptr)));
    if (!actor)
        return;
    const sead::Vector3f origin = _168.getTranslation();
    const f32 height = sub_71009221DC();
    const sead::Vector3f world_offset = *mAtOffsetWorld_s;
    const sead::Vector3f local_offset = *mAtOffsetLocal_s;
    const sead::Matrix34f transform = actor->getMainBody()->getTransform();
    sead::Vector3f rotated;
    rotated.setRotated(transform, local_offset);
    rotated.y = 0.0f;
    _118 = origin + ((sead::Vector3f::ey * height + world_offset) + rotated);
}

// NON_MATCHING: scalar/vector copies and prepared-field loads differ.
void CameraMotorcycleLockOnEmpty::sub_710077C7A4() {
    if (auto* camera = getCamera()) {
        const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
        const sead::Vector3f forward = _168.getBase(2);
        _10c = forward.x == -0.0f && forward.z == -0.0f ? 0.0f :
                   angleStuff(std::atan2(-forward.x, -forward.z) * 57.295776f);
    }
    sub_710077CC90();
    _114 = sead::lerp(*mCameraRadiusSlow_s, *mCameraRadiusFast_s, _108);
    sub_710077CDA4();
    _124 = sead::lerp(*mFovySlow_s, *mFovyFast_s, _108);
}

// NON_MATCHING: RTTI guards, quaternion/vector copies and float scheduling differ.
void CameraMotorcycleLockOnEmpty::sub_710077BED8() {
    auto* actor = sead::DynamicCast<act::Motorcycle>(sead::DynamicCast<ksys::act::Actor>(
        ksys::act::PlayerInfo::instance()->getHorseLink().getProc(nullptr, nullptr)));
    if (!actor)
        return;
    sead::Matrix33f basis = sead::Matrix33f::ident;
    sead::Vector3f forward = actor->getMtx().getBase(2);
    forward.y = 0.0f;
    const f32 forward_length = forward.length();
    if (forward_length > 0.0f)
        forward *= 1.0f / forward_length;
    sead::Vector3f right = sead::Vector3f::ey.cross(forward);
    const f32 right_length = right.length();
    if (right_length > 0.0f)
        right *= 1.0f / right_length;
    const bool valid = right.squaredLength() > 0.01f && forward.squaredLength() > 0.01f;
    if (valid) {
        basis.setBase(0, right);
        basis.setBase(1, sead::Vector3f::ey);
        basis.setBase(2, forward);
    }
    const sead::Vector3f target_pos = actor->getMtx().getTranslation();
    sead::Quatf target;
    basis.toQuat(target);
    const sead::Vector3f old_pos = _168.getTranslation();
    sead::Quatf rotation;
    _168.toQuat(rotation);
    if (valid) {
        const f32 rate = ksys::VFR::getLerpFactor(_198 *
            sead::Mathf::clamp(*mCameraFollowRotCushion_s, 0.0f, 1.0f));
        rotation.slerpTo(rotation, target, rate);
    }
    _168.makeQT(rotation, sead::Vector3f::zero);
    forward = _168.getBase(2);
    forward.y = 0.0f;
    const f32 new_forward_length = forward.length();
    if (new_forward_length > 0.0f)
        forward *= 1.0f / new_forward_length;
    right = sead::Vector3f::ey.cross(forward);
    const f32 new_right_length = right.length();
    if (new_right_length > 0.0f)
        right *= 1.0f / new_right_length;
    const sead::Vector3f delta = target_pos - old_pos;
    const f32 vertical = delta.dot(sead::Vector3f::ey);
    const f32 horizontal_rate = ksys::VFR::getLerpFactor(
        sead::Mathf::clamp(*mCameraFollowPosCushionX_s, 0.0f, 1.0f));
    const f32 vertical_rate = ksys::VFR::getLerpFactor(sead::Mathf::clamp(
        vertical > 0.0f ? *mCameraFollowPosCushionYUp_s : *mCameraFollowPosCushionYDown_s,
        0.0f, 1.0f));
    const f32 forward_rate = ksys::VFR::getLerpFactor(
        sead::Mathf::clamp(*mCameraFollowPosCushionZ_s, 0.0f, 1.0f));
    _168.setTranslation(old_pos + right * delta.dot(right) * horizontal_rate +
                         sead::Vector3f::ey * vertical * vertical_rate +
                         forward * delta.dot(forward) * forward_rate);
}

// NON_MATCHING: RTTI guards, frame and bound scalar scheduling differ.
void CameraMotorcycleLockOnEmpty::sub_710077CA0C() {
    auto* actor = sead::DynamicCast<act::Motorcycle>(sead::DynamicCast<ksys::act::Actor>(
        ksys::act::PlayerInfo::instance()->getHorseLink().getProc(nullptr, nullptr)));
    if (!actor)
        return;
    const f32 frame = ksys::VFR::instance()->getDeltaTime();
    const f32 difference = angleStuff(_10c - _128);
    const f32 rate = ksys::VFR::getLerpFactor(
        sead::Mathf::clamp(*mAutoLngBaseCushion_s, 0.0f, 1.0f));
    f32 step = angleStuff(difference * rate);
    f32 max = frame * *mAutoLngMaxRotSpeed_s;
    if (angleStuff(step) > angleStuff(max)) {
        step = angleStuff(max);
    } else {
        max = -max;
        if (angleStuff(step) < angleStuff(max))
            step = angleStuff(max);
    }
    _128 = angleStuff(step + _128);
}

// NON_MATCHING: quaternion/vector copies, RTTI guards and float scheduling differ.
void CameraMotorcycleLockOnEmpty::m34() {
    auto* camera = getCamera();
    if (!camera)
        return;
    auto* actor = sead::DynamicCast<act::Motorcycle>(sead::DynamicCast<ksys::act::Actor>(
        ksys::act::PlayerInfo::instance()->getHorseLink().getProc(nullptr, nullptr)));
    if (!actor)
        return;
    sub_710077B7DC();
    const sead::Matrix34f transform = actor->getMainBody()->getTransform();
    const f32 tilt = transform.getBase(2).cross(sead::Vector3f::ey).length();
    _198 = tilt * tilt * tilt * tilt;
    if (_164)
        sub_710077BD98();
    sub_710077BED8();
    sub_710077C7A4();
    if (_164) {
        sub_710077C8A8();
        _160 = 1.0f;
        _164 = false;
    }
    ksys::VFR::lerp(&_160, 0.0f, sead::Mathf::clamp(*mSwitchingCushionRate_s, 0.0f, 1.0f));
    act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    const f32 blend = _160;
    sub_710077CA0C();
    polar._8 = angleStuff(angleStuff(blend * _144) + _128);
    _12c = angleStuff(angleStuff(sub_7100791E44(sead::Mathf::clamp(
        *mAutoLatitudeB2ICushion_s, 0.0f, 1.0f)) * angleStuff(_110 - _12c)) + _12c);
    polar._4 = angleStuff(sub_7100924CAC(angleStuff(angleStuff(blend * _148) + _12c)));
    _130 += sub_7100791E44(sead::Mathf::clamp(*mCameraRadiusB2ICushion_s, 0.0f, 1.0f)) *
            (_114 - _130);
    polar._0 = _130 + blend * _14c;
    _140 += sub_7100791E44(sead::Mathf::clamp(*mFovyBaseCushion_s, 0.0f, 1.0f)) * (_124 - _140);
    camera->_860._0._24 = _140 + blend * _15c;
    _134 = _118;
    camera->_860._0._c = _118 + _150 * blend;
    camera->_860._0._0 = camera->_860._0._c + polar.sub_7100923254();
    camera->sub_71007953C8();
}

}  // namespace uking::action
