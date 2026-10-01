#include "Game/AI/AI/aiMimicFlagSelect.h"

namespace uking::ai {

MimicFlagSelect::MimicFlagSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MimicFlagSelect::~MimicFlagSelect() = default;

bool MimicFlagSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool MimicFlagSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool MimicFlagSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void MimicFlagSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mIsMimicry_m)
        changeChild("擬態", params);
    else
        changeChild("通常", params);
}

void MimicFlagSelect::calc_() {}

void MimicFlagSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MimicFlagSelect::loadParams_() {
    getMapUnitParam(&mIsMimicry_m, "IsMimicry");
}

}  // namespace uking::ai
