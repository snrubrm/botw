#include "Game/AI/AI/aiGolemChemicalVanishedSelect.h"

namespace uking::ai {

GolemChemicalVanishedSelect::GolemChemicalVanishedSelect(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

GolemChemicalVanishedSelect::~GolemChemicalVanishedSelect() = default;

bool GolemChemicalVanishedSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool GolemChemicalVanishedSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool GolemChemicalVanishedSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GolemChemicalVanishedSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GolemChemicalVanishedSelect::calc_() {}

void GolemChemicalVanishedSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GolemChemicalVanishedSelect::loadParams_() {
    getAITreeVariable(&mGolemChemicalController_a, "GolemChemicalController");
}

}  // namespace uking::ai
