#include "Game/AI/AI/aiRegistedActorNumTwoSelectBase.h"

namespace uking::ai {

RegistedActorNumTwoSelectBase::RegistedActorNumTwoSelectBase(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

RegistedActorNumTwoSelectBase::~RegistedActorNumTwoSelectBase() = default;

bool RegistedActorNumTwoSelectBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RegistedActorNumTwoSelectBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RegistedActorNumTwoSelectBase::calc_() {}

void RegistedActorNumTwoSelectBase::m34(int num, ksys::act::ai::InlineParamPack* params) {}

void RegistedActorNumTwoSelectBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RegistedActorNumTwoSelectBase::loadParams_() {
    getAITreeVariable(&mRegistedActorUnit_a, "RegistedActorUnit");
}

bool RegistedActorNumTwoSelectBase::isFailed() const {
    return getCurrentChild()->isFailed() || mFlags.isOn(Flag::Failed);
}

bool RegistedActorNumTwoSelectBase::isFinished() const {
    return getCurrentChild()->isFinished() || mFlags.isOn(Flag::Finished);
}

}  // namespace uking::ai
