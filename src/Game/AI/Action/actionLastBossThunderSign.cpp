#include "Game/AI/Action/actionLastBossThunderSign.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "math/seadMathCalcCommon.h"

namespace uking::action {

LastBossThunderSign::LastBossThunderSign(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LastBossThunderSign::~LastBossThunderSign() = default;

bool LastBossThunderSign::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LastBossThunderSign::enter_(ksys::act::ai::InlineParamPack* params) {
    _28 = ksys::Timer(*mSignTime_s, *mSignTime_s);
    if (auto* chemical = mActor->getChemicalStuff())
        chemical->sub_7100D90FF0(true);
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
