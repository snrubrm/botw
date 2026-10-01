#include "Game/AI/AI/aiNearCreateAppearTypeSelect.h"

namespace uking::ai {

NearCreateAppearTypeSelect::NearCreateAppearTypeSelect(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

NearCreateAppearTypeSelect::~NearCreateAppearTypeSelect() = default;

bool NearCreateAppearTypeSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the two tail-call blocks are laid out in the opposite order
void NearCreateAppearTypeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mNearCreateAppearType_m == 1)
        changeChild("空中", params);
    else
        changeChild("通常", params);
}

void NearCreateAppearTypeSelect::calc_() {}

void NearCreateAppearTypeSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NearCreateAppearTypeSelect::loadParams_() {
    getMapUnitParam(&mNearCreateAppearType_m, "NearCreateAppearType");
}

bool NearCreateAppearTypeSelect::isFinished() const {
    return mFlags.isOn(Flag::Finished) || getCurrentChild()->isFinished();
}

bool NearCreateAppearTypeSelect::isFailed() const {
    return mFlags.isOn(Flag::Failed) || getCurrentChild()->isFailed();
}

}  // namespace uking::ai
