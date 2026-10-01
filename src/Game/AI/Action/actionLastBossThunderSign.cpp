#include "Game/AI/Action/actionLastBossThunderSign.h"
#include "math/seadMathCalcCommon.h"

namespace uking::action {

LastBossThunderSign::LastBossThunderSign(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LastBossThunderSign::~LastBossThunderSign() = default;

bool LastBossThunderSign::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LastBossThunderSign::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void LastBossThunderSign::leave_() {
    ksys::act::ai::Action::leave_();
}

void LastBossThunderSign::loadParams_() {
    getStaticParam(&mSignTime_s, "SignTime");
}

void LastBossThunderSign::calc_() {
    _28.update();
    if (_28.value <= sead::Mathf::epsilon())
        setFinished();
}

}  // namespace uking::action
