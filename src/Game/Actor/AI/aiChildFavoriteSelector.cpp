#include "Game/Actor/AI/aiChildFavoriteSelector.h"
#include "Game/Actor/aiUnk_71007368A4.h"

namespace uking::ai {

ChildFavoriteSelector::ChildFavoriteSelector(const InitArg& arg) : ChildSelector(arg) {}

ChildFavoriteSelector::~ChildFavoriteSelector() = default;

bool ChildFavoriteSelector::init_(sead::Heap* heap) {
    return ChildSelector::init_(heap);
}

void ChildFavoriteSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    ChildSelector::enter_(params);
}

void ChildFavoriteSelector::calc_() {
    ChildSelector::calc_();
}

void ChildFavoriteSelector::leave_() {
    ChildSelector::leave_();
}

void ChildFavoriteSelector::loadParams_() {
    ChildSelector::loadParams_();
}

bool ChildFavoriteSelector::m34(ksys::act::BaseProc* proc) {
    return sub_710073A010(mActor, proc);
}

}  // namespace uking::ai
