#include "Game/AI/Action/actionSetTargetFrameMtx.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SetTargetFrameMtx::SetTargetFrameMtx(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetTargetFrameMtx::~SetTargetFrameMtx() = default;

bool SetTargetFrameMtx::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetTargetFrameMtx::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SetTargetFrameMtx::leave_() {
    if (*mResetTransBoneOnLeave_s) {
        if (auto* as_list = mActor->getASList())
            as_list->sub_710115CD0C();
    }
}

void SetTargetFrameMtx::loadParams_() {
    getStaticParam(&mTargetIdx_s, "TargetIdx");
    getStaticParam(&mSeqBankIdx_s, "SeqBankIdx");
    getStaticParam(&mTargetFrame_s, "TargetFrame");
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
    getStaticParam(&mResetTransBoneOnLeave_s, "ResetTransBoneOnLeave");
    getStaticParam(&mIsHomeMtx_s, "IsHomeMtx");
    getStaticParam(&mASName_s, "ASName");
}

void SetTargetFrameMtx::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
