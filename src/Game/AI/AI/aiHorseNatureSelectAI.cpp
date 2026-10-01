#include "Game/AI/AI/aiHorseNatureSelectAI.h"

namespace uking::ai {

HorseNatureSelectAI::HorseNatureSelectAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HorseNatureSelectAI::~HorseNatureSelectAI() = default;

bool HorseNatureSelectAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HorseNatureSelectAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void HorseNatureSelectAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HorseNatureSelectAI::loadParams_() {}

bool HorseNatureSelectAI::isFinished() const {
    auto* child = getCurrentChild();
    if (ActionBase::isFinished())
        return true;
    return child && child->isFinished();
}

bool HorseNatureSelectAI::isFailed() const {
    auto* child = getCurrentChild();
    if (ActionBase::isFailed())
        return true;
    return child && child->isFailed();
}

void HorseNatureSelectAI::calc_() {
    auto* child = getCurrentChild();
    if (!child)
        return;
    if (child->isFinished())
        setFinished();
    else if (child->isFailed())
        setFailed();
}

}  // namespace uking::ai
