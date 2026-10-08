#include "Game/AI/Action/actionCameraTail.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

CameraTail::CameraTail(const InitArg& arg) : CameraAction(arg) {}

CameraTail::~CameraTail() = default;

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
