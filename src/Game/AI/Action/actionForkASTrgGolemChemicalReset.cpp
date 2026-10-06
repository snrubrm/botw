#include "Game/AI/Action/actionForkASTrgGolemChemicalReset.h"
#include "Game/AI/aiUnk_7102450410.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

ForkASTrgGolemChemicalReset::ForkASTrgGolemChemicalReset(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkASTrgGolemChemicalReset::~ForkASTrgGolemChemicalReset() = default;

bool ForkASTrgGolemChemicalReset::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkASTrgGolemChemicalReset::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void ForkASTrgGolemChemicalReset::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkASTrgGolemChemicalReset::loadParams_() {
    getAITreeVariable(&mGolemChemicalController_a, "GolemChemicalController");
}

void ForkASTrgGolemChemicalReset::calc_() {
    if (sub_71005DD780(mActor, 71, nullptr, 0, 0)) {
        if (auto* controller = sead::DynamicCast<Unk_7102450410>(
                *static_cast<Unk_71025afb58**>(mGolemChemicalController_a))) {
            for (s32 i = 0; i < controller->_8.size(); ++i)
                controller->_8[i].sub_71007086AC();
        }
    }
}

}  // namespace uking::action
