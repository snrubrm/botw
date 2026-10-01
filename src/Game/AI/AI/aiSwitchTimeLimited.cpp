#include "Game/AI/AI/aiSwitchTimeLimited.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/VFR.h"

namespace uking::ai {

SwitchTimeLimited::SwitchTimeLimited(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SwitchTimeLimited::~SwitchTimeLimited() = default;

bool SwitchTimeLimited::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SwitchTimeLimited::enter_(ksys::act::ai::InlineParamPack* params) {
    _40 = 0.0f;
    changeChild("オフ");
}

// NON_MATCHING: the chase target is loaded before the VFR delta (see SwitchTimeLag::calc_)
void SwitchTimeLimited::calc_() {
    auto* actor = mActor;
    const bool on = actor->checkBasicSig();
    if (isCurrentChild("オフ")) {
        if (on) {
            _40 = 0.0f;
            changeChild("オン");
        }
        return;
    }

    if (!isCurrentChild("オン"))
        return;

    if (on) {
        _40 = 0.0f;
        return;
    }

    actor->m107();
    if (sead::Mathf::chase(&_40, *mWaitTime_m, ksys::VFR::instance()->getDeltaFrame())) {
        _40 = 0.0f;
        changeChild("オフ");
    }
}

void SwitchTimeLimited::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SwitchTimeLimited::loadParams_() {
    getMapUnitParam(&mWaitTime_m, "WaitTime");
}

}  // namespace uking::ai
