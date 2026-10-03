#include "Game/AI/AI/aiSwitchTimeLag.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/VFR.h"

namespace uking::ai {

SwitchTimeLag::SwitchTimeLag(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SwitchTimeLag::~SwitchTimeLag() = default;

bool SwitchTimeLag::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SwitchTimeLag::enter_(ksys::act::ai::InlineParamPack* params) {
    _40 = 0.0f;
}

// NON_MATCHING: scheduling of the `_40 = 0.0f` store against the string address of changeChild("オフ")
void SwitchTimeLag::calc_() {
    auto* actor = mActor;
    if (!actor->checkBasicSig()) {
        _40 = 0.0f;
        if (!isCurrentChild("オフ")) {
            _40 = 0.0f;
            changeChild("オフ");
        }
        return;
    }

    bool done;
    if (ksys::VFR::chase(&_40, *mWaitTime_m)) {
        done = true;
    } else {
        actor->m107();
        done = false;
    }

    if (!isCurrentChild("オン") && done) {
        _40 = 0.0f;
        changeChild("オン");
    }
}

void SwitchTimeLag::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SwitchTimeLag::loadParams_() {
    getMapUnitParam(&mWaitTime_m, "WaitTime");
}

}  // namespace uking::ai
