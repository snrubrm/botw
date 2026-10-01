#include "Game/AI/AI/aiMotorcycleRootBase.h"

namespace uking::ai {

MotorcycleRootBase::MotorcycleRootBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MotorcycleRootBase::~MotorcycleRootBase() = default;

bool MotorcycleRootBase::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool MotorcycleRootBase::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool MotorcycleRootBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void MotorcycleRootBase::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710043EABC(params);
}

void MotorcycleRootBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MotorcycleRootBase::loadParams_() {}

void MotorcycleRootBase::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed())
        return;
    if (child->isChangeable())
        sub_710043EABC(nullptr);
}

}  // namespace uking::ai
