#include "Game/AI/AI/aiRangeCheckSeqTwoAction.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

RangeCheckSeqTwoAction::RangeCheckSeqTwoAction(const InitArg& arg) : SeqTargetTwoAction(arg) {}

RangeCheckSeqTwoAction::~RangeCheckSeqTwoAction() = default;

bool RangeCheckSeqTwoAction::init_(sead::Heap* heap) {
    return SeqTargetTwoAction::init_(heap);
}

void RangeCheckSeqTwoAction::enter_(ksys::act::ai::InlineParamPack* params) {
    const sead::Vector3f target_pos = *mTargetPos_d;
    const sead::Vector3f& pos = mActor->getMtx().getTranslation();
    const f32 dist_sq =
        sead::Mathf::square(target_pos.x - pos.x) + sead::Mathf::square(target_pos.z - pos.z);
    const f32 range_sq = sead::Mathf::square(*mRange_s);
    const bool in_range = *mCheckFar_s ? dist_sq > range_sq : dist_sq < range_sq;

    ksys::act::ai::InlineParamPack child_params;
    if (in_range) {
        child_params.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("後行動", &child_params);
    } else {
        child_params.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("先行動", &child_params);
    }
}

void RangeCheckSeqTwoAction::calc_() {
    SeqTargetTwoAction::calc_();
}

void RangeCheckSeqTwoAction::leave_() {
    SeqTargetTwoAction::leave_();
}

void RangeCheckSeqTwoAction::loadParams_() {
    SeqTargetTwoAction::loadParams_();
    getStaticParam(&mRange_s, "Range");
    getStaticParam(&mCheckFar_s, "CheckFar");
}

}  // namespace uking::ai
