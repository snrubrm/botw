#include "Game/AI/Action/actionWindmill_Wing.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>

namespace uking::action {

Windmill_Wing::Windmill_Wing(const InitArg& arg) : ksys::act::ai::Action(arg) {}

Windmill_Wing::~Windmill_Wing() = default;

bool Windmill_Wing::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void Windmill_Wing::enter_(ksys::act::ai::InlineParamPack* params) {
    _58 = sead::GlobalRandom::instance()->getF32() * sead::Mathf::piHalf();
    m32(true);
    m33();
    if (*mIsTurnToWindDir_s)
        m34(1.0f);
}

void Windmill_Wing::leave_() {
    ksys::act::ai::Action::leave_();
}

void Windmill_Wing::loadParams_() {
    getStaticParam(&mStartFrameRange_s, "StartFrameRange");
    getStaticParam(&mASPlaySpeedMin_s, "ASPlaySpeedMin");
    getStaticParam(&mASPlaySpeedMax_s, "ASPlaySpeedMax");
    getStaticParam(&mASPlaySpeedMinWindPower_s, "ASPlaySpeedMinWindPower");
    getStaticParam(&mASPlaySpeedMaxWindPower_s, "ASPlaySpeedMaxWindPower");
    getStaticParam(&mTurnRate_s, "TurnRate");
    getStaticParam(&mIsTurnToWindDir_s, "IsTurnToWindDir");
}

void Windmill_Wing::calc_() {
    m32(false);
    if (*mIsTurnToWindDir_s)
        m34(0.0f);
}

void Windmill_Wing::m33() {
    playAS("Rotate", false, 0, 0, -1.0f);
}

}  // namespace uking::action
