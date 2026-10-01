#include "Game/AI/AI/aiRegistedActorNumTwoSelect.h"

namespace uking::ai {

RegistedActorNumTwoSelect::RegistedActorNumTwoSelect(const InitArg& arg)
    : RegistedActorNumTwoSelectBase(arg) {}

RegistedActorNumTwoSelect::~RegistedActorNumTwoSelect() = default;

bool RegistedActorNumTwoSelect::init_(sead::Heap* heap) {
    return RegistedActorNumTwoSelectBase::init_(heap);
}

void RegistedActorNumTwoSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    RegistedActorNumTwoSelectBase::enter_(params);
}

void RegistedActorNumTwoSelect::calc_() {
    RegistedActorNumTwoSelectBase::calc_();
}

void RegistedActorNumTwoSelect::leave_() {
    RegistedActorNumTwoSelectBase::leave_();
}

void RegistedActorNumTwoSelect::loadParams_() {
    RegistedActorNumTwoSelectBase::loadParams_();
    getStaticParam(&mNum_s, "Num");
}

void RegistedActorNumTwoSelect::m34(int num, ksys::act::ai::InlineParamPack* params) {
    if (*mNum_s < num)
        changeChild("より多い", params);
    else
        changeChild("以下", params);
}

}  // namespace uking::ai
