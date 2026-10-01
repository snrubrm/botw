#include "Game/AI/AI/aiChildHaveSelect.h"

namespace uking::ai {

ChildHaveSelect::ChildHaveSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ChildHaveSelect::~ChildHaveSelect() = default;

bool ChildHaveSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ChildHaveSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool ChildHaveSelect::isFailed() const {
    if (ksys::act::ai::Ai::isFailed())
        return true;
    if (!getCurrentChild())
        return false;
    return getCurrentChild()->isFailed();
}

bool ChildHaveSelect::isFinished() const {
    if (ksys::act::ai::Ai::isFinished())
        return true;
    if (!getCurrentChild())
        return false;
    return getCurrentChild()->isFinished();
}

void ChildHaveSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ChildHaveSelect::loadParams_() {
    getStaticParam(&mIsCheckEveryFrame_s, "IsCheckEveryFrame");
}

}  // namespace uking::ai
