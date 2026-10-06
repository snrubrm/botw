#include "Game/AI/Action/actionPlayASForDemo.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

PlayASForDemo::PlayASForDemo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PlayASForDemo::~PlayASForDemo() = default;

bool PlayASForDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PlayASForDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void PlayASForDemo::leave_() {
    ksys::act::ai::Action::leave_();
}

void PlayASForDemo::loadParams_() {
    getStaticParam(&mAnimeDrivenSettings_s, "AnimeDrivenSettings");
    getDynamicParam(&mTargetIndex_d, "TargetIndex");
    getDynamicParam(&mSeqBank_d, "SeqBank");
    getDynamicParam(&mIsEnabledAnimeDriven_d, "IsEnabledAnimeDriven");
    getDynamicParam(&mClothWarpMode_d, "ClothWarpMode");
    getDynamicParam(&mMorphingFrame_d, "MorphingFrame");
    getDynamicParam(&mIsIgnoreSame_d, "IsIgnoreSame");
    getDynamicParam(&mASName_d, "ASName");
}

void PlayASForDemo::calc_() {
    ksys::act::ai::Action::calc_();
}

bool PlayASForDemo::m33() {
    return false;
}

float PlayASForDemo::m32() {
    if (auto* as_list = mActor->getASList())
        return as_list->x_5(0, 0, &ksys::as::ASList::Unk2::sub_71011632F8);
    return 0.0f;
}

const sead::SafeString& PlayASForDemo::m34() {
    auto* as_list = mActor->getASList();
    if (!as_list || mASName_d.isEmpty())
        return sead::SafeString::cEmptyString;
    as_list->sub_710115AA68(mASName_d);
    return mASName_d;
}

// NON_MATCHING: the original keeps the morphing frame / -1 choice as branches (`ldr s0; fcmp; b.ge; fmov s0, #-1`),
// ours selects with a register move
void PlayASForDemo::m36() {
    if (*mTargetIndex_d == -1) {
        auto* as_list = mActor->getASList();
        if (!as_list)
            return;
        const sead::SafeString& name = m34();
        _a4 = as_list->sub_710115BC28(name, (*mTargetIndex_d != -1 || *mMorphingFrame_d < 0.0f) ?
                                                -1.0f : *mMorphingFrame_d);
        return;
    }

    const sead::SafeString& name = m34();
    playAS(name.cstr(), *mIsIgnoreSame_d, *mTargetIndex_d == -1 ? 0 : *mTargetIndex_d,
           *mTargetIndex_d == -1 ? 0 : *mSeqBank_d, -1.0f);
    _a4 = *mTargetIndex_d == -1 ? 0 : *mTargetIndex_d;
}

}  // namespace uking::action
