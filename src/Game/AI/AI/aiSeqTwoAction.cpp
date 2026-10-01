#include "Game/AI/AI/aiSeqTwoAction.h"

namespace uking::ai {

SeqTwoAction::SeqTwoAction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool SeqTwoAction::isFailed() const {
    if (mFlags.isOn(Flag::Failed))
        return true;

    return (*mIsFinishedByFailAction_s || isCurrentChild("後行動")) && getCurrentChild()->isFailed();
}

bool SeqTwoAction::isFinished() const {
    if (mFlags.isOn(Flag::Finished) || m34())
        return true;

    if (isCurrentChild("後行動"))
        return getCurrentChild()->isFinished();

    return false;
}

bool SeqTwoAction::isChangeable() const {
    if (*mIsNoChangeable_s)
        return false;

    auto* child = getCurrentChild();
    if (child->isChangeable())
        return true;

    if (!*mIsEndChangeable_s)
        return false;

    return child->isFinished() || child->isFailed();
}

void SeqTwoAction::enter_(ksys::act::ai::InlineParamPack* params) {
    if (handlePendingChildChange())
        return;

    if (m36())
        changeChild("後行動", params);
    else
        changeChild("先行動", params);
}

void SeqTwoAction::calc_() {
    auto* child = getCurrentChild();

    if (m35() && isCurrentChild("先行動")) {
        changeChild("後行動");
        return;
    }

    if (m34()) {
        setFinished();
        return;
    }

    if (!child->isFinished() && !child->isFailed())
        return;

    if (child->isFailed() && *mIsFinishedByFailAction_s) {
        setFailed();
        return;
    }

    if (isCurrentChild("先行動")) {
        changeChild("後行動");
        return;
    }

    if (child->isFinished())
        setFinished();
    else
        setFailed();
}

void SeqTwoAction::loadParams_() {
    getStaticParam(&mIsFinishedByFailAction_s, "IsFinishedByFailAction");
    getStaticParam(&mIsEndChangeable_s, "IsEndChangeable");
    getStaticParam(&mIsNoChangeable_s, "IsNoChangeable");
}

void SeqTwoAction::handlePendingChildChange_() {
    changeChild(mPendingChildIdx);
}

}  // namespace uking::ai
