#include "Game/AI/AI/aiCameraRoot.h"
#include "Game/Actor/actCameraUtil.h"

namespace uking::ai {

CameraRoot::CameraRoot(const InitArg& arg) : CameraAI(arg) {}

CameraRoot::~CameraRoot() = default;

bool CameraRoot::m34(sead::Heap* heap) {
    mFlags.set(Flag::Changeable);
    return true;
}

void CameraRoot::m35(ksys::act::ai::InlineParamPack* params) {
    _58 = 0x25;
    _59 = 0x25;
    _54 = 45.0f;
    _5a = false;
    sub_710078F434();
    setFinished();

    auto* camera = getCamera();
    if (!camera)
        return;

    camera->_860._7f8.change(1, camera->_860._7fa.isOn(1));
    camera->_860._804.sub_710079AE20(0x100);
    camera->_860._804.sub_710079AE20(0x20000);
    camera->_860._815[1] = 0;
}

void CameraRoot::sub_710078F434() {
    auto* camera = getCamera();
    if (!camera)
        return;

    auto& state = camera->_860;
    if (state._1d0._18 == 1.0f || angleStuff(state._1b8) != angleStuff(0) ||
        angleStuff(state._1bc) != angleStuff(0) || state._1c0 != 0 || state._1c4 != 0 ||
        state._1a0 != sead::Vector3f(0, 0, 0)) {
        if (state._1c8 != 0) {
            state._0 = state._38 = state._70 = state._a8 = state._e0;
        } else {
            camera->sub_7100795E08(state._0, &state._0);
            state._38 = state._0;
        }
        state._1a0 = {0, 0, 0};
        state._1b8 = angleStuff(0);
        state._1bc = angleStuff(0);
        state._1c0 = 0;
        state._1c4 = 0;
    }
}

void CameraRoot::m37() {
    auto* camera = getCamera();
    if (!camera)
        return;

    camera->_860._81b[1] = 0;
    camera->_860._7f8.reset(1);
    camera->_860._804.sub_710079AE40(0x100);
    camera->_860._815[1] = 0;
}

void CameraRoot::m38() {
    // Same null check + DynamicCast form as Unk_7102459708::getCamera (matching).
    if (!mActor)
        return;
    auto* camera = sead::DynamicCast<act::Camera>(mActor);
    if (!camera)
        return;

    getStaticParam(&camera->_860._198, "sideOffsetBowCus");
    getStaticParam(&camera->_860._1f0, "guardianDist");
    getStaticParam(&camera->_860._1f8, "guardianAngle");
}

}  // namespace uking::ai
