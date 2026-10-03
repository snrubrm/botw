#include "Game/AI/Action/actionCameraEventTurn.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

CameraEventTurn::CameraEventTurn(const InitArg& arg) : CameraEvent(arg) {}

CameraEventTurn::~CameraEventTurn() = default;

void CameraEventTurn::m43() {
    const u32 revise_mode = *mReviseModeRunning_d;
    _84 = 0;
    _d8 = revise_mode < 3 ? revise_mode : 1;
    _88.sub_710079C384(*mCount_d, 0.0f);
    if (auto* camera = getCamera())
        _4c = camera->_860._0;
}

// NON_MATCHING: the original loads the x / y of the target through integer registers and loads
// the polar angles in the opposite order (regalloc / scheduling only)
void CameraEventTurn::m44() {
    auto* camera = getCamera();
    if (!camera)
        return;

    act::Unk_7100922700 from(_4c._c - _4c._0);
    _88.sub_710079C408();

    f32 t = 1.0f;
    if (_84 < *mCount_d) {
        ksys::Timer::update(&_84, 1.0f);
        const f32 cushion = *mCushion_d;
        t = cushion + (1.0f - cushion) * _88._18;
    }

    sead::Vector3f target;
    if (auto* cam = getCameraActor()) {
        target.set(*mPosX_d, *mPosY_d, *mPosZ_d);
        const auto& state = cam->_860._0;
        if (state._0 == target)
            target += state._c - state._0;
    }

    act::Unk_7100922700 to(target - camera->_860._0._0);
    from._4 = angleStuff(angleStuff(t * angleStuff(to._4 - from._4)) + from._4);
    from._8 = angleStuff(angleStuff(t * angleStuff(to._8 - from._8)) + from._8);
    camera->_860._0._c = camera->_860._0._0 + from.sub_7100923254();

    if (*mCount_d <= _84)
        setFinished();

    camera->_860._818 = 0;
    if (_d8 == 2)
        camera->_860._818 = 1;
    else if (_d8 == 0)
        camera->_860._818 = 2;
}

void CameraEventTurn::m46() {
    getDynamicParam_2(&mReviseModeRunning_d, "ReviseModeRunning");
    getDynamicParam_2(&mPosX_d, "PosX");
    getDynamicParam_2(&mPosY_d, "PosY");
    getDynamicParam_2(&mPosZ_d, "PosZ");
    getDynamicParam_2(&mCount_d, "Count");
    getDynamicParam_2(&mCushion_d, "Cushion");
}

}  // namespace uking::action
