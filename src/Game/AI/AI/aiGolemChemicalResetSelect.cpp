#include "Game/AI/AI/aiGolemChemicalResetSelect.h"
#include "Game/AI/aiUnk_7102450410.h"

namespace uking::ai {

GolemChemicalResetSelect::GolemChemicalResetSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GolemChemicalResetSelect::~GolemChemicalResetSelect() = default;

bool GolemChemicalResetSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GolemChemicalResetSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* controller = sead::DynamicCast<Unk_7102450410>(*mGolemChemicalController_a);
    if (controller && controller->_8.size() >= 1 && controller->_8(0)._b0 == 4)
        changeChild("ケミカル復帰", params);
    else
        changeChild("通常", params);
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

void GolemChemicalResetSelect::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("ケミカル復帰"))
            changeChild("通常");
    } else {
        child->isChangeable();
    }
}

}  // namespace uking::ai
