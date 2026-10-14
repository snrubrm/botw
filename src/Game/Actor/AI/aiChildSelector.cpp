#include "Game/Actor/AI/aiChildSelector.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

ChildSelector::ChildSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ChildSelector::~ChildSelector() = default;

bool ChildSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ChildSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* child = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild());
    if (m34(child))
        changeChild("成立", params);
    else
        changeChild("非成立", params);
}

void ChildSelector::calc_() {
    if (!*mIsCheckEveryFrame_s)
        return;
    if (!getCurrentChild()->isChangeable())
        return;

    auto* child = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild());
    if (m34(child)) {
        if (!isCurrentChild("成立"))
            changeChild("成立");
    } else {
        if (!isCurrentChild("非成立"))
            changeChild("非成立");
    }
}

bool ChildSelector::isFinished() const {
    return getCurrentChild()->isFinished();
}

void ChildSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ChildSelector::loadParams_() {
    getStaticParam(&mIsNoChildForceEnd_s, "IsNoChildForceEnd");
    getStaticParam(&mIsCheckEveryFrame_s, "IsCheckEveryFrame");
}

bool ChildSelector::isFailed() const {
    if (isFinished())
        return false;
    if (getCurrentChild()->isFailed())
        return true;
    if (!*mIsNoChildForceEnd_s)
        return false;
    return mActor->getConnectedCalcChild() == nullptr;
}

bool ChildSelector::m34(ksys::act::BaseProc* proc) {
    return false;
}

}  // namespace uking::ai
