#include "Game/AI/AI/aiSeqIfFailAction.h"

namespace uking::ai {

SeqIfFailAction::SeqIfFailAction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SeqIfFailAction::~SeqIfFailAction() = default;

bool SeqIfFailAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SeqIfFailAction::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("先行動", params);
}

void SeqIfFailAction::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("先行動") && child->isFailed())
            changeChild("先行動失敗");
        return;
    }
    child->isChangeable();
}

bool SeqIfFailAction::isFailed() const {
    return isCurrentChild("先行動失敗") && getCurrentChild()->isFailed();
}

bool SeqIfFailAction::isChangeable() const {
    if (ksys::act::ai::Ai::isChangeable())
        return true;
    if (!*mIsEndChangeable_s)
        return false;
    auto* child = getCurrentChild();
    return child->isFinished() || child->isFailed();
}

void SeqIfFailAction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SeqIfFailAction::loadParams_() {
    getStaticParam(&mIsEndChangeable_s, "IsEndChangeable");
}

}  // namespace uking::ai
