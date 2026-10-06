#include "Game/AI/Action/actionForkOnLeaveGolemChemReset.h"
#include "Game/AI/aiUnk_7102450410.h"

namespace uking::action {

ForkOnLeaveGolemChemReset::ForkOnLeaveGolemChemReset(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkOnLeaveGolemChemReset::~ForkOnLeaveGolemChemReset() = default;

bool ForkOnLeaveGolemChemReset::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkOnLeaveGolemChemReset::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void ForkOnLeaveGolemChemReset::leave_() {
    if (auto* controller = sead::DynamicCast<Unk_7102450410>(
            *static_cast<Unk_71025afb58**>(mGolemChemicalController_a))) {
        for (s32 i = 0; i < controller->_8.size(); ++i)
            controller->_8[i].sub_71007086AC();
    }
}

void ForkOnLeaveGolemChemReset::loadParams_() {
    getAITreeVariable(&mGolemChemicalController_a, "GolemChemicalController");
}

void ForkOnLeaveGolemChemReset::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
