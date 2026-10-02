#include "Game/AI/AI/aiSeqTrgPartsNotice.h"

namespace uking::ai {

SeqTrgPartsNotice::SeqTrgPartsNotice(const InitArg& arg) : SeqTwoAction(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
SeqTrgPartsNotice::~SeqTrgPartsNotice() {
    ;
}

bool SeqTrgPartsNotice::init_(sead::Heap* heap) {
    return SeqTwoAction::init_(heap);
}

void SeqTrgPartsNotice::enter_(ksys::act::ai::InlineParamPack* params) {
    SeqTwoAction::enter_(params);
}

void SeqTrgPartsNotice::leave_() {
    SeqTwoAction::leave_();
}

void SeqTrgPartsNotice::loadParams_() {
    SeqTwoAction::loadParams_();
    getStaticParam(&mPartsName_s, "PartsName");
    getStaticParam(&mIsFinishByNoNoticeActionEnd_s, "IsFinishByNoNoticeActionEnd");
}

}  // namespace uking::ai
