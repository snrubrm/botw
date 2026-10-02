#include "Game/AI/AI/aiGolemChemicalVanishedSelect.h"
#include "Game/AI/aiUnk_7102450410.h"

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
    auto* controller = sead::DynamicCast<Unk_7102450410>(
        *static_cast<Unk_71025afb58**>(mGolemChemicalController_a));
    if (sub_71007090F4(controller))
        changeChild("ケミカル消失", params);
    else
        changeChild("通常", params);
}

void GolemChemicalVanishedSelect::calc_() {}

void GolemChemicalVanishedSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GolemChemicalVanishedSelect::loadParams_() {
    getAITreeVariable(&mGolemChemicalController_a, "GolemChemicalController");
}

}  // namespace uking::ai
