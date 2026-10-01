#include "Game/AI/AI/aiGolemChemicalResetSelect.h"

namespace uking::ai {

GolemChemicalResetSelect::GolemChemicalResetSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GolemChemicalResetSelect::~GolemChemicalResetSelect() = default;

bool GolemChemicalResetSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GolemChemicalResetSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GolemChemicalResetSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GolemChemicalResetSelect::loadParams_() {
    getAITreeVariable(&mGolemChemicalController_a, "GolemChemicalController");
}

bool GolemChemicalResetSelect::isFinished() const {
    return isCurrentChild("通常") && getCurrentChild()->isFinished();
}

bool GolemChemicalResetSelect::isFailed() const {
    return ActionBase::isFailed() || (isCurrentChild("通常") && getCurrentChild()->isFailed());
}

}  // namespace uking::ai
