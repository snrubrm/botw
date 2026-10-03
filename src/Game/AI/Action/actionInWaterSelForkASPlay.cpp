#include "Game/AI/Action/actionInWaterSelForkASPlay.h"

namespace uking::action {

inWaterSelForkASPlay::inWaterSelForkASPlay(const InitArg& arg) : ksys::act::ai::Action(arg) {}

inWaterSelForkASPlay::~inWaterSelForkASPlay() = default;

bool inWaterSelForkASPlay::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void inWaterSelForkASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void inWaterSelForkASPlay::leave_() {
    ksys::act::ai::Action::leave_();
}

void inWaterSelForkASPlay::loadParams_() {
    getStaticParam(&mEndState_s, "EndState");
    getStaticParam(&mChangeableTiming_s, "ChangeableTiming");
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
    getStaticParam(&mFirstRandomRatio_s, "FirstRandomRatio");
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
    getStaticParam(&mASName_s, "ASName");
}

void inWaterSelForkASPlay::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
