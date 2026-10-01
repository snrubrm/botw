#include "Game/AI/AI/aiSwitchTimer.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/VFR.h"

namespace uking::ai {

SwitchTimer::SwitchTimer(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SwitchTimer::~SwitchTimer() = default;

bool SwitchTimer::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SwitchTimer::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (actor->checkLinkBasicSig() ||
        (actor->hasPlacementLinkForBasicSig() && actor->checkBasicSig())) {
        _40 = 0.0f;
        changeChild("オン待機");
    } else {
        _40 = 0.0f;
        changeChild("オフ待機");
    }
}

// NON_MATCHING: *mWaitTime_m is loaded before the VFR delta (original: after; see SwitchRightAndWrong::calc_)
void SwitchTimer::calc_() {
    auto* actor = mActor;
    getCurrentChild();
    actor->m107();

    if (actor->hasPlacementLinkForBasicSig() && !actor->checkBasicSig()) {
        _40 = 0.0f;
        if (!isCurrentChild("オフ")) {
            _40 = 0.0f;
            changeChild("オフ");
        }
        return;
    }

    if (!sead::Mathf::chase(&_40, *mWaitTime_m, ksys::VFR::instance()->getDeltaFrame()))
        return;

    if (isCurrentChild("オフ待機") || isCurrentChild("オフ")) {
        _40 = 0.0f;
        changeChild("オン");
    } else if (isCurrentChild("オン待機") || isCurrentChild("オン")) {
        _40 = 0.0f;
        changeChild("オフ");
    }
}

void SwitchTimer::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SwitchTimer::loadParams_() {
    getMapUnitParam(&mWaitTime_m, "WaitTime");
}

}  // namespace uking::ai
