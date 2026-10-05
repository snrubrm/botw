#include "Game/AI/AI/aiHiddenOctarockSearchTarget.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

HiddenOctarockSearchTarget::HiddenOctarockSearchTarget(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

HiddenOctarockSearchTarget::~HiddenOctarockSearchTarget() = default;

bool HiddenOctarockSearchTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HiddenOctarockSearchTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("飛び出す", params);
}

void HiddenOctarockSearchTarget::leave_() {
    mActor->m93(0, 0.0f);
}

// NON_MATCHING: the output vector and parameter pack occupy different stack locations.
void HiddenOctarockSearchTarget::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("飛び出す")) {
            mActor->m93(2, 0.0f);
            changeChild("出現待機");
        } else if (isCurrentChild("出現待機")) {
            setFailed();
        } else if (isCurrentChild("気づき")) {
            setFinished();
        }
    } else if (child->isChangeable() && !isCurrentChild("気づき")) {
        sead::Vector3f position;
        if (sub_7100432B0C(&position)) {
            mActor->m93(4, 0.0f);
            ksys::act::ai::InlineParamPack params;
            params.addVec3(position, "TargetPos", -1);
            changeChild("気づき", &params);
        }
    }

    if (sub_71005DD780(mActor, 59, nullptr, 0, 0) && isCurrentChild("飛び出す"))
        mActor->m93(2, 0.0f);
}

void HiddenOctarockSearchTarget::loadParams_() {
    getStaticParam(&mNoticeTerrorLevel_s, "NoticeTerrorLevel");
    getStaticParam(&mNoticeWorryRange_s, "NoticeWorryRange");
}

}  // namespace uking::ai
