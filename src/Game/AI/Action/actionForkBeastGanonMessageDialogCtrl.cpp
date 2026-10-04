#include "Game/AI/Action/actionForkBeastGanonMessageDialogCtrl.h"

namespace uking::action {

ForkBeastGanonMessageDialogCtrl::ForkBeastGanonMessageDialogCtrl(const InitArg& arg)
    : SimpleMessageDialogCtrl(arg) {}

ForkBeastGanonMessageDialogCtrl::~ForkBeastGanonMessageDialogCtrl() = default;

bool ForkBeastGanonMessageDialogCtrl::init_(sead::Heap* heap) {
    return SimpleMessageDialogCtrl::init_(heap);
}

void ForkBeastGanonMessageDialogCtrl::enter_(ksys::act::ai::InlineParamPack* params) {
    SimpleMessageDialogCtrl::enter_(params);
}

void ForkBeastGanonMessageDialogCtrl::leave_() {
    SimpleMessageDialogCtrl::leave_();
    *mInBeastGanonVoiceSequence_a = false;
}

void ForkBeastGanonMessageDialogCtrl::loadParams_() {
    SimpleMessageDialogCtrl::loadParams_();
    getAITreeVariable(&mGanonBeastVoiceSequenceCount_a, "GanonBeastVoiceSequenceCount");
    getAITreeVariable(&mInBeastGanonVoiceSequence_a, "InBeastGanonVoiceSequence");
}

// NON_MATCHING: the original branches on the type check and calls sub_7100721FB4 from both arms (with `obj + 8` and nullptr);
// ours selects the argument with one csel (+0x20 bytes: x21 saved for the pre-incremented `obj + 8`)
void ForkBeastGanonMessageDialogCtrl::calc_() {
    SimpleMessageDialogCtrl::calc_();
    bool in_sequence = _28.getData()->sub_7100721FB4();
    if (!in_sequence)
        in_sequence = *mGanonBeastVoiceSequenceCount_a > 0;
    *mInBeastGanonVoiceSequence_a = in_sequence;
}

}  // namespace uking::action
