#include "Game/AI/AI/aiSeqTwoWeakPointOnFirstDo.h"

namespace uking::ai {

SeqTwoWeakPointOnFirstDo::SeqTwoWeakPointOnFirstDo(const InitArg& arg) : SeqTwoAction(arg) {}

SeqTwoWeakPointOnFirstDo::~SeqTwoWeakPointOnFirstDo() = default;

bool SeqTwoWeakPointOnFirstDo::init_(sead::Heap* heap) {
    return SeqTwoAction::init_(heap);
}

void SeqTwoWeakPointOnFirstDo::enter_(ksys::act::ai::InlineParamPack* params) {
    SeqTwoAction::enter_(params);
}

void SeqTwoWeakPointOnFirstDo::calc_() {
    SeqTwoAction::calc_();
}

void SeqTwoWeakPointOnFirstDo::leave_() {
    SeqTwoAction::leave_();
}

void SeqTwoWeakPointOnFirstDo::loadParams_() {
    SeqTwoAction::loadParams_();
    getAITreeVariable(&mIsWeakPointAppearMode_a, "IsWeakPointAppearMode");
}

bool SeqTwoWeakPointOnFirstDo::m36() const {
    return !*mIsWeakPointAppearMode_a;
}

}  // namespace uking::ai
