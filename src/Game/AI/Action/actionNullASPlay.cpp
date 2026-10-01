#include "Game/AI/Action/actionNullASPlay.h"

namespace uking::action {

NullASPlay::NullASPlay(const InitArg& arg) : ksys::act::ai::Action(arg) {}

bool NullASPlay::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NullASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS(mASName_s.cstr(), *mIsIgnoreSame_s, *mTargetIdx_s, *mSeqBankIdx_s, -1.0f);
    mFlags.set(Flag::Changeable);
}

void NullASPlay::leave_() {
    ksys::act::ai::Action::leave_();
}

void NullASPlay::loadParams_() {
    getStaticParam(&mTargetIdx_s, "TargetIdx");
    getStaticParam(&mSeqBankIdx_s, "SeqBankIdx");
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
    getStaticParam(&mASName_s, "ASName");
}

void NullASPlay::calc_() {
    if (isFinishedAS(*mTargetIdx_s, *mSeqBankIdx_s))
        setFinished();
}

}  // namespace uking::action
