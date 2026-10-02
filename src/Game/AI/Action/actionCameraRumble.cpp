#include "Game/AI/Action/actionCameraRumble.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/System/Vibration.h"

namespace uking::action {

CameraRumble::CameraRumble(const InitArg& arg) : ksys::act::ai::Action(arg) {}

bool CameraRumble::oneShot_() {
    if (auto* vibration = ksys::Vibration::instance()) {
        const s32 count = *mCount_d;
        _40 = sead::Mathi::clamp(count, 1, 255);
        const ksys::Vibration::Unk2 request(*mPattern_d, sead::Vector3f::zero, 4, nullptr, *mPower_d,
                                            100.0f,
                                            *mSideways_d ? sead::Vector3f::ex : sead::Vector3f::ey,
                                            _40);
        vibration->sub_71010BB800(request);
    }
    return true;
}

void CameraRumble::loadParams_() {
    getDynamicParam_2(&mPattern_d, "Pattern");
    getDynamicParam_2(&mCount_d, "Count");
    getDynamicParam_2(&mPower_d, "Power");
    getDynamicParam_2(&mSideways_d, "Sideways");
}

}  // namespace uking::action
