#include "Game/AI/Action/actionForkEmitExpandFieldWithCreate.h"
#include "Game/Actor/actUnk_7100d3cd74.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkEmitExpandFieldWithCreate::ForkEmitExpandFieldWithCreate(const InitArg& arg)
    : ForkEmitExpandField(arg) {}

ForkEmitExpandFieldWithCreate::~ForkEmitExpandFieldWithCreate() = default;

bool ForkEmitExpandFieldWithCreate::init_(sead::Heap* heap) {
    return ForkEmitExpandField::init_(heap);
}

void ForkEmitExpandFieldWithCreate::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkEmitExpandField::enter_(params);
    sub_710014E780(&mActor->getMtx());
}

void ForkEmitExpandFieldWithCreate::leave_() {
    ForkEmitExpandField::leave_();
}

void ForkEmitExpandFieldWithCreate::loadParams_() {
    ForkEmitExpandField::loadParams_();
    getStaticParam(&mScaleTime_s, "ScaleTime");
    getStaticParam(&mIsReuseActor_s, "IsReuseActor");
    getStaticParam(&mIsSetPartsLink_s, "IsSetPartsLink");
}

void ForkEmitExpandFieldWithCreate::calc_() {
    ForkEmitExpandField::calc_();
}

// NON_MATCHING: the original tests `parts != nullptr && *mIsSetPartsLink_s` with `cmp; ccmp` and returns `_a8` on the
// fall-through path; ours branches on each operand and swaps the two blocks
ksys::act::BaseProcLink& ForkEmitExpandFieldWithCreate::m32() {
    auto* parts = mActor->m101();
    const bool is_set_parts_link = *mIsSetPartsLink_s;
    if (parts && is_set_parts_link)
        return parts->getActorPartsActor(mPartsKey_s);
    return _a8;
}

}  // namespace uking::action
