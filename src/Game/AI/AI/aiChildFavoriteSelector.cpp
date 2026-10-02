#include "Game/AI/AI/aiChildFavoriteSelector.h"
#include "Game/AI/aiUnk_71007368A4.h"

namespace uking::ai {

ChildFavoriteSelector::ChildFavoriteSelector(const InitArg& arg) : ChildFavoriteSelectorBase(arg) {}

ChildFavoriteSelector::~ChildFavoriteSelector() = default;

bool ChildFavoriteSelector::init_(sead::Heap* heap) {
    return ChildFavoriteSelectorBase::init_(heap);
}

void ChildFavoriteSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    ChildFavoriteSelectorBase::enter_(params);
}

void ChildFavoriteSelector::calc_() {
    ChildFavoriteSelectorBase::calc_();
}

void ChildFavoriteSelector::leave_() {
    ChildFavoriteSelectorBase::leave_();
}

void ChildFavoriteSelector::loadParams_() {
    ChildFavoriteSelectorBase::loadParams_();
}

bool ChildFavoriteSelector::m34(ksys::act::BaseProc* proc) {
    return sub_710073A010(mActor, proc);
}

}  // namespace uking::ai
