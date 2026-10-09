#include "Game/AI/Action/actionCameraAiming.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::action {

CameraAiming::CameraAiming(const InitArg& arg) : CameraAction(arg) {}

CameraAiming::~CameraAiming() = default;

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

// NON_MATCHING: interpolation and transform scalar scheduling differ.
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
