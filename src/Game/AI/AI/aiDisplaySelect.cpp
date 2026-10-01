#include "Game/AI/AI/aiDisplaySelect.h"

namespace uking::ai {

DisplaySelect::DisplaySelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DisplaySelect::~DisplaySelect() = default;

bool DisplaySelect::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool DisplaySelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool DisplaySelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DisplaySelect::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_7100361960(params);
}

void DisplaySelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DisplaySelect::loadParams_() {
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mIsCheckEveryFrame_s, "IsCheckEveryFrame");
}

}  // namespace uking::ai
