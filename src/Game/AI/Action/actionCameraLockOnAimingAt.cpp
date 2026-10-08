#include "Game/AI/Action/actionCameraLockOnAimingAt.h"
#include <cmath>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include <math/seadMathCalcCommon.h>

namespace uking::action {

CameraLockOnAimingAt::CameraLockOnAimingAt(const InitArg& arg) : CameraAction(arg) {}

CameraLockOnAimingAt::~CameraLockOnAimingAt() = default;

void CameraLockOnAimingAt::m33() {
    _4c.sub_71008A4644();
    _128.reset();
    _138.set(0, 0, 0);
    if (auto* camera = getCamera())
        camera->_860._7f8.reset(1);
}

void CameraLockOnAimingAt::m36() {
    getStaticParam(&mLatMin_s, "LatMin");
    getStaticParam(&mLatMax_s, "LatMax");
    getStaticParam(&mInputRangeNearDist_s, "InputRangeNearDist");
    getStaticParam(&mLatInputRange_s, "LatInputRange");
    getStaticParam(&mLngInputRange_s, "LngInputRange");
    getStaticParam(&mInputRangeFarDist_s, "InputRangeFarDist");
    getStaticParam(&mLatInputRangeFar_s, "LatInputRangeFar");
    getStaticParam(&mLngInputRangeFar_s, "LngInputRangeFar");
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mOffsetX_s, "OffsetX");
    getStaticParam(&mOffsetY_s, "OffsetY");
    getStaticParam(&mFovy_s, "Fovy");
    getStaticParam(&mGyro_s, "Gyro");
}

void CameraLockOnAimingAt::sub_71007749F8() {
    const f32 dist = std::sqrt((_144.x - _150.x) * (_144.x - _150.x) +
                               (_144.z - _150.z) * (_144.z - _150.z));
    f32 ratio;
    if (dist == 0.0f)
        ratio = 1.0f;
    else
        ratio = sead::Mathf::clamp(*mOffsetX_s / dist, -1.0f, 1.0f);
    const f32 angle = std::asin(ratio);
    const act::Unk_7100922700 polar(_144 - _150);
    _168 = angleStuff(sead::Mathf::rad2deg(angle) + polar._8);
}

void CameraLockOnAimingAt::sub_7100775368(ksys::act::BaseProcLink* link) {
    ksys::act::BaseProc* target = sub_7100926A14();
    if (!target)
        return;

    if (sub_7100926D24()) {
        auto* proc = ksys::act::PlayerInfo::instance()->getHorseLink().getProc(nullptr, nullptr);
        if (sead::IsDerivedFrom<ksys::act::Actor>(proc))
            link->acquire(proc, false);
        else
            link->acquire(target, false);
    } else {
        link->acquire(target, false);
    }
}

}  // namespace uking::action
