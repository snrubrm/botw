#include "Game/AI/Action/actionEnvSeEmitPointBirdPlayAction.h"
#include "KingSystem/Utils/InitTimeInfo.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>

namespace uking::action {

namespace {
ksys::util::InitConstants sInitConstants;
ksys::util::InitTimeInfo sInitTimeInfo;
}  // namespace

EnvSeEmitPointBirdPlayAction::EnvSeEmitPointBirdPlayAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EnvSeEmitPointBirdPlayAction::~EnvSeEmitPointBirdPlayAction() = default;

bool EnvSeEmitPointBirdPlayAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EnvSeEmitPointBirdPlayAction::enter_(ksys::act::ai::InlineParamPack* params) {
    _20.setNow();
    f32 rate = sub_7100FEA4E4();
    s64 milliseconds;
    if (rate > 0.0f) {
        rate = sead::Mathf::clampMin(rate, 0.2f);
        milliseconds = static_cast<s64>(
            sead::GlobalRandom::instance()->getF32Range(0.5f / rate, 8.0f / rate) * 1000.0f);
    } else {
        milliseconds = -1000;
    }
    _28.setMilliSeconds(milliseconds);
    _30.setNow();
}

void EnvSeEmitPointBirdPlayAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EnvSeEmitPointBirdPlayAction::loadParams_() {}

void EnvSeEmitPointBirdPlayAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
