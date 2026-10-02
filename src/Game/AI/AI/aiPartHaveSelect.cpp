#include "Game/AI/AI/aiPartHaveSelect.h"

namespace uking::ai {

PartHaveSelect::PartHaveSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
PartHaveSelect::~PartHaveSelect() {
    ;
}

bool PartHaveSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PartHaveSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71004F4758(params);
}

void PartHaveSelect::calc_() {
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed() && child->isChangeable() &&
        *mIsCheckEveryFrame_s) {
        sub_71004F4758(nullptr);
    }
}

void PartHaveSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PartHaveSelect::loadParams_() {
    getStaticParam(&mIsCheckEveryFrame_s, "IsCheckEveryFrame");
    getStaticParam(&mPartsKey_s, "PartsKey");
}

}  // namespace uking::ai
