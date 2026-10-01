#include "Game/AI/AI/aiChildHaveSelect.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

ChildHaveSelect::ChildHaveSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ChildHaveSelect::~ChildHaveSelect() = default;

bool ChildHaveSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ChildHaveSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (mActor->getConnectedCalcChild())
        changeChild("子所持", params);
    else
        changeChild("非子所持", params);
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

void ChildHaveSelect::calc_() {
    if (!*mIsCheckEveryFrame_s)
        return;

    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed() && !child->isChangeable())
        return;

    if (mActor->getConnectedCalcChild()) {
        if (isCurrentChild("非子所持"))
            changeChild("子所持");
    } else {
        if (isCurrentChild("子所持"))
            changeChild("非子所持");
    }
}

}  // namespace uking::ai
