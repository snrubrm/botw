#include "Game/AI/Action/actionSetFrameASPlay.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SetFrameASPlay::SetFrameASPlay(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetFrameASPlay::~SetFrameASPlay() = default;

bool SetFrameASPlay::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetFrameASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* as_list = mActor->getASList();
    playAS(mASName_s.cstr(), *mIsIgnoreSame_s, *mTargetIdx_s, *mSeqBankIdx_s, -1.0f);
    if (as_list) {
        const f32 frame = *mASFrame_m;
        as_list->x_3(*mTargetIdx_s, *mSeqBankIdx_s, &ksys::as::ASList::Unk2::sub_7101163298, frame);
    }
    mFlags.set(Flag::Changeable);
}

void SetFrameASPlay::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetFrameASPlay::loadParams_() {
    getStaticParam(&mTargetIdx_s, "TargetIdx");
    getStaticParam(&mSeqBankIdx_s, "SeqBankIdx");
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
    getStaticParam(&mASName_s, "ASName");
    getMapUnitParam(&mASFrame_m, "ASFrame");
}

void SetFrameASPlay::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
