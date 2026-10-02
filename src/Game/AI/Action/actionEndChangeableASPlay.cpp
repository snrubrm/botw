#include "Game/AI/Action/actionEndChangeableASPlay.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

EndChangeableASPlay::EndChangeableASPlay(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EndChangeableASPlay::~EndChangeableASPlay() = default;

bool EndChangeableASPlay::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EndChangeableASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS(mASName_s.cstr(), *mIsIgnoreSame_s, *mTargetIdx_s, *mSeqBankIdx_s, -1.0f);
}

void EndChangeableASPlay::leave_() {
    ksys::act::ai::Action::leave_();
}

void EndChangeableASPlay::loadParams_() {
    getStaticParam(&mTargetIdx_s, "TargetIdx");
    getStaticParam(&mSeqBankIdx_s, "SeqBankIdx");
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
    getStaticParam(&mASName_s, "ASName");
}

void EndChangeableASPlay::calc_() {
    bool ended = false;
    if (auto* as_list = mActor->getASList())
        ended = as_list->x_7(*mTargetIdx_s, *mSeqBankIdx_s, &ksys::as::ASList::Unk2::sub_7101162FE8);
    const bool finished = isFinishedAS(*mTargetIdx_s, *mSeqBankIdx_s);
    if (ended || finished)
        mFlags.set(Flag::Changeable);
    else
        mFlags.reset(Flag::Changeable);
}

}  // namespace uking::action
