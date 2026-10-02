#include "Game/AI/AI/aiChildFavoriteSelectorBase.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

ChildFavoriteSelectorBase::ChildFavoriteSelectorBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ChildFavoriteSelectorBase::~ChildFavoriteSelectorBase() = default;

bool ChildFavoriteSelectorBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ChildFavoriteSelectorBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
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
