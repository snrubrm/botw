#include "Game/AI/Action/actionCameraRotRumble.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/System/Vibration.h"

namespace uking::action {

CameraRotRumble::CameraRotRumble(const InitArg& arg) : ksys::act::ai::Action(arg) {}

bool CameraRotRumble::oneShot_() {
    if (auto* vibration = ksys::Vibration::instance()) {
        const s32 count = *mCount_d;
        _38 = sead::Mathi::clamp(count, 1, 255);
        const ksys::Vibration::Unk1 request(*mPattern_d, sead::Vector3f::zero, 4, nullptr, *mPower_d,
                                            100.0f, _38);
        vibration->sub_71010BB808(request);
    }
    return true;
}

void CameraRotRumble::loadParams_() {
    getDynamicParam_2(&mPattern_d, "Pattern");
    getDynamicParam_2(&mCount_d, "Count");
    getDynamicParam_2(&mPower_d, "Power");
}

}  // namespace uking::action
