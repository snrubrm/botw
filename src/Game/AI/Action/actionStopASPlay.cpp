#include "Game/AI/Action/actionStopASPlay.h"

namespace uking::action {

StopASPlay::StopASPlay(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

void StopASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
    if (!mASName_s.isEmpty())
        playAS(mASName_s.cstr(), *mIsIgnoreSame_s, 0, 0, -1.0f);
}

void StopASPlay::leave_() {}

// NON_MATCHING: same calls; the original computes `this + 0x30` before the first getStaticParam (extra callee-saved register)
void StopASPlay::loadParams_() {
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
    ActionWithPosAngReduce::loadParams_();
}

void StopASPlay::calc_() {
    ActionWithPosAngReduce::calc_();
}

}  // namespace uking::action
