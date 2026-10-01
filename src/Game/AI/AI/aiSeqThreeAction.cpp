#include "Game/AI/AI/aiSeqThreeAction.h"

namespace uking::ai {

SeqThreeAction::SeqThreeAction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SeqThreeAction::~SeqThreeAction() = default;

bool SeqThreeAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

bool SeqThreeAction::isFailed() const {
    if (mFlags.isOn(Flag::Failed))
        return true;

    return (*mIsFinishedByFailAction_s || isCurrentChild("後行動")) && getCurrentChild()->isFailed();
}

bool SeqThreeAction::isFinished() const {
    if (mFlags.isOn(Flag::Finished))
        return true;

    if (isCurrentChild("後行動"))
        return getCurrentChild()->isFinished();

    return false;
}

bool SeqThreeAction::isChangeable() const {
    if (*mIsNoChangeable_s)
        return false;

    if (Ai::isChangeable())
        return true;

    if (!*mIsEndChangeable_s)
        return false;

    auto* child = getCurrentChild();
    return child->isFinished() || child->isFailed();
}

void SeqThreeAction::enter_(ksys::act::ai::InlineParamPack* params) {
    if (handlePendingChildChange())
        return;

    changeChild("先行動", params);
}

void SeqThreeAction::calc_() {
    auto* child = getCurrentChild();

    if (!child->isFinished() && !child->isFailed())
        return;

    if (*mIsFinishedByFailAction_s && child->isFailed()) {
        setFailed();
        return;
    }

    if (isCurrentChild("先行動"))
        changeChild("中行動");
    else if (isCurrentChild("中行動"))
        changeChild("後行動");
    else if (child->isFinished())
        setFinished();
    else
        setFailed();
}

void SeqThreeAction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SeqThreeAction::loadParams_() {
    getStaticParam(&mIsFinishedByFailAction_s, "IsFinishedByFailAction");
    getStaticParam(&mIsEndChangeable_s, "IsEndChangeable");
    getStaticParam(&mIsNoChangeable_s, "IsNoChangeable");
}

void SeqThreeAction::handlePendingChildChange_() {
    changeChild(mPendingChildIdx);
}

}  // namespace uking::ai
