#include "Game/AI/AI/aiRandomSelectThreeAction.h"

namespace uking::ai {

RandomSelectThreeAction::RandomSelectThreeAction(const InitArg& arg)
    : RandomSelectThreeActionBase(arg) {}

RandomSelectThreeAction::~RandomSelectThreeAction() = default;

bool RandomSelectThreeAction::init_(sead::Heap* heap) {
    return RandomSelectThreeActionBase::init_(heap);
}

void RandomSelectThreeAction::enter_(ksys::act::ai::InlineParamPack* params) {
    RandomSelectThreeActionBase::enter_(params);
}

void RandomSelectThreeAction::calc_() {
    RandomSelectThreeActionBase::calc_();
}

void RandomSelectThreeAction::leave_() {
    RandomSelectThreeActionBase::leave_();
}

void RandomSelectThreeAction::loadParams_() {
    RandomSelectThreeActionBase::loadParams_();
    getStaticParam(&mRateActionA_s, "RateActionA");
    getStaticParam(&mRateActionB_s, "RateActionB");
    getStaticParam(&mRateActionC_s, "RateActionC");
}

f32 RandomSelectThreeAction::m34() {
    return *mRateActionA_s;
}

f32 RandomSelectThreeAction::m35() {
    return *mRateActionB_s;
}

f32 RandomSelectThreeAction::m36() {
    return *mRateActionC_s;
}

}  // namespace uking::ai
