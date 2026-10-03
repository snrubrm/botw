#include "Game/AI/AI/aiChildFavoriteSelectorBase.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

ChildFavoriteSelectorBase::ChildFavoriteSelectorBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ChildFavoriteSelectorBase::~ChildFavoriteSelectorBase() = default;

bool ChildFavoriteSelectorBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ChildFavoriteSelectorBase::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* child = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild());
    if (m34(child))
        changeChild("成立", params);
    else
        changeChild("非成立", params);
}

void ChildFavoriteSelectorBase::calc_() {
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

bool ChildFavoriteSelectorBase::isFinished() const {
    return getCurrentChild()->isFinished();
}

void ChildFavoriteSelectorBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ChildFavoriteSelectorBase::loadParams_() {
    getStaticParam(&mIsNoChildForceEnd_s, "IsNoChildForceEnd");
    getStaticParam(&mIsCheckEveryFrame_s, "IsCheckEveryFrame");
}

bool ChildFavoriteSelectorBase::isFailed() const {
    if (isFinished())
        return false;
    if (getCurrentChild()->isFailed())
        return true;
    if (!*mIsNoChildForceEnd_s)
        return false;
    return mActor->getConnectedCalcChild() == nullptr;
}

bool ChildFavoriteSelectorBase::m34(ksys::act::BaseProc* proc) {
    return false;
}

}  // namespace uking::ai
