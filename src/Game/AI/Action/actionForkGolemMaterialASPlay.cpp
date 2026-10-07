#include "Game/AI/Action/actionForkGolemMaterialASPlay.h"
#include "Game/AI/aiUnk_7102450410.h"

namespace uking::action {

ForkGolemMaterialASPlay::ForkGolemMaterialASPlay(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkGolemMaterialASPlay::~ForkGolemMaterialASPlay() = default;

bool ForkGolemMaterialASPlay::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: part-mode validation is combined into a range comparison.
void ForkGolemMaterialASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* controller = sead::DynamicCast<Unk_7102450410>(*mGolemChemicalController_a);
    if (!controller) {
        setFailed();
        return;
    }
    s32 type = *mTargetPartType_s;
    // The part count and storage remain fixed for the original traversal.
    auto entries = controller->_8;
    switch (type) {
    case 1:
    case 2:
        break;
    case 3:
        for (auto& entry : entries)
            entry.sub_7100708A44(mASName_s);
        mFlags.set(Flag::Changeable);
        return;
    default:
        type = 0;
        break;
    }
    for (auto& entry : entries) {
        if (entry._a8 == type) {
            entry.sub_7100708A44(mASName_s);
            break;
        }
    }
    mFlags.set(Flag::Changeable);
}

void ForkGolemMaterialASPlay::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkGolemMaterialASPlay::loadParams_() {
    getStaticParam(&mTargetPartType_s, "TargetPartType");
    getStaticParam(&mASName_s, "ASName");
    getAITreeVariable(&mGolemChemicalController_a, "GolemChemicalController");
}

void ForkGolemMaterialASPlay::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
