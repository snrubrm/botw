#include "Game/AI/Action/actionTreasureBoxOpenWait.h"

namespace uking::action {

TreasureBoxOpenWait::TreasureBoxOpenWait(const InitArg& arg) : ksys::act::ai::Action(arg) {}

TreasureBoxOpenWait::~TreasureBoxOpenWait() = default;

bool TreasureBoxOpenWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void TreasureBoxOpenWait::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!*mIsOpenTreasureBox_a && !mASName_PreOpen_s.isEmpty())
        playAS(mASName_PreOpen_s.cstr(), *mIsIgnoreSame_s, *mTargetIdx_s, *mSeqBankIdx_s, -1.0f);
    else
        playAS(mASName_s.cstr(), *mIsIgnoreSame_s, *mTargetIdx_s, *mSeqBankIdx_s, -1.0f);
    mFlags.set(Flag::Changeable);
}

void TreasureBoxOpenWait::leave_() {
    ksys::act::ai::Action::leave_();
}

void TreasureBoxOpenWait::loadParams_() {
    getStaticParam(&mTargetIdx_s, "TargetIdx");
    getStaticParam(&mSeqBankIdx_s, "SeqBankIdx");
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mASName_PreOpen_s, "ASName_PreOpen");
    getAITreeVariable(&mIsOpenTreasureBox_a, "IsOpenTreasureBox");
}

void TreasureBoxOpenWait::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
