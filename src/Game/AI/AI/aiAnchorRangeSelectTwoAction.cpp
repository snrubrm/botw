#include "Game/AI/AI/aiAnchorRangeSelectTwoAction.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

AnchorRangeSelectTwoAction::AnchorRangeSelectTwoAction(const InitArg& arg)
    : RangeSelectTwoAction(arg) {}

AnchorRangeSelectTwoAction::~AnchorRangeSelectTwoAction() = default;

bool AnchorRangeSelectTwoAction::init_(sead::Heap* heap) {
    return RangeSelectTwoAction::init_(heap);
}

void AnchorRangeSelectTwoAction::enter_(ksys::act::ai::InlineParamPack* params) {
    RangeSelectTwoAction::enter_(params);
}

void AnchorRangeSelectTwoAction::calc_() {
    RangeSelectAction::calc_();
}

void AnchorRangeSelectTwoAction::leave_() {
    RangeSelectTwoAction::leave_();
}

void AnchorRangeSelectTwoAction::loadParams_() {
    RangeSelectTwoAction::loadParams_();
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mAnchorName_s, "AnchorName");
}

// NON_MATCHING: the original computes the x difference separately in both branches (ours hoists
// it) and loads anchor.y before target.y in the 3D branch
f32 AnchorRangeSelectTwoAction::m35() {
    auto* anchor = ksys::act::findLinkReferenceObj(mActor, mAnchorName_s,
                                                   sead::SafeString::cEmptyString, nullptr);
    if (!anchor)
        return -1.0f;

    const auto& anchor_pos = anchor->getTranslate();
    const auto& target_pos = *mTargetPos_d;
    if (*mIsRangeXZ_s)
        return sead::Vector2f(target_pos.x - anchor_pos.x, target_pos.z - anchor_pos.z).length();
    return (target_pos - anchor_pos).length();
}

}  // namespace uking::ai
