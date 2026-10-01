#include "Game/AI/AI/aiSeqIfElseAction.h"

namespace uking::ai {

SeqIfElseAction::SeqIfElseAction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SeqIfElseAction::~SeqIfElseAction() = default;

bool SeqIfElseAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SeqIfElseAction::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("先行動", params);
}

void SeqIfElseAction::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("先行動")) {
            if (child->isFailed())
                changeChild("先行動失敗");
            else
                changeChild("後行動");
        }
        return;
    }
    child->isChangeable();
}

void SeqIfElseAction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SeqIfElseAction::loadParams_() {
    getStaticParam(&mFailType_s, "FailType");
}

bool SeqIfElseAction::isFinished() const {
    switch (*mFailType_s) {
    case 1:
        if (isCurrentChild("先行動"))
            return false;
        return getCurrentChild()->isFinished();
    case 2: {
        if (!isCurrentChild("後行動"))
            return false;
        auto* child = getCurrentChild();
        if (child->isFinished())
            return true;
        return child->isFailed();
    }
    default: {
        if (isCurrentChild("先行動"))
            return false;
        auto* child = getCurrentChild();
        if (child->isFinished())
            return true;
        return child->isFailed();
    }
    }
}

bool SeqIfElseAction::isFailed() const {
    switch (*mFailType_s) {
    case 1:
        if (isCurrentChild("先行動"))
            return false;
        return getCurrentChild()->isFailed();
    case 2: {
        if (!isCurrentChild("先行動失敗"))
            return false;
        auto* child = getCurrentChild();
        if (child->isFinished())
            return true;
        return child->isFailed();
    }
    default:
        return false;
    }
}

}  // namespace uking::ai
