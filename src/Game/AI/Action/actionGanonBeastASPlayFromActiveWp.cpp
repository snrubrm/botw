#include "Game/AI/Action/actionGanonBeastASPlayFromActiveWp.h"

namespace uking::action {

GanonBeastASPlayFromActiveWp::GanonBeastASPlayFromActiveWp(const InitArg& arg)
    : ForkASPlayBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
GanonBeastASPlayFromActiveWp::~GanonBeastASPlayFromActiveWp() {
    ;
}

bool GanonBeastASPlayFromActiveWp::init_(sead::Heap* heap) {
    return ForkASPlayBase::init_(heap);
}

void GanonBeastASPlayFromActiveWp::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkASPlayBase::enter_(params);
}

void GanonBeastASPlayFromActiveWp::leave_() {
    ForkASPlayBase::leave_();
}

void GanonBeastASPlayFromActiveWp::loadParams_() {
    ForkASPlayBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
    getAITreeVariable(&mWeakPointActiveFlag_a, "WeakPointActiveFlag");
}

void GanonBeastASPlayFromActiveWp::calc_() {
    ForkASPlayBase::calc_();
}

const char* GanonBeastASPlayFromActiveWp::m32() {
    return _68.cstr();
}

}  // namespace uking::action
