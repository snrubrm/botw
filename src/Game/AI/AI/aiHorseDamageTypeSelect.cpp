#include "Game/AI/AI/aiHorseDamageTypeSelect.h"

namespace uking::ai {

HorseDamageTypeSelect::HorseDamageTypeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HorseDamageTypeSelect::~HorseDamageTypeSelect() = default;

bool HorseDamageTypeSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HorseDamageTypeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void HorseDamageTypeSelect::calc_() {
    if (getCurrentChild()->isFinished())
        setFinished();
    else if (getCurrentChild()->isFailed())
        setFailed();
}

void HorseDamageTypeSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HorseDamageTypeSelect::loadParams_() {}

bool HorseDamageTypeSelect::isFinished() const {
    auto* child = getCurrentChild();
    if (ActionBase::isFinished())
        return true;
    return child && child->isFinished();
}

bool HorseDamageTypeSelect::isFailed() const {
    auto* child = getCurrentChild();
    if (ActionBase::isFailed())
        return true;
    return child && child->isFailed();
}

}  // namespace uking::ai
