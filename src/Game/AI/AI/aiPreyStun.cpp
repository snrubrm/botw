#include "Game/AI/AI/aiPreyStun.h"
#include <math/seadMathCalcCommon.h>

namespace uking::ai {

PreyStun::PreyStun(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PreyStun::~PreyStun() = default;

bool PreyStun::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PreyStun::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PreyStun::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        setFinished();
        return;
    }

    if (!isCurrentChild("気絶中") || _40.value <= sead::Mathf::epsilon())
        return;

    _40.update();
    if (_40.value <= sead::Mathf::epsilon())
        changeChild("復帰");
}

void PreyStun::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PreyStun::loadParams_() {
    getStaticParam(&mStunTime_s, "StunTime");
}

}  // namespace uking::ai
