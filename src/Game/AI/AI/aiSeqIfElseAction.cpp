#include "Game/AI/AI/aiSeqIfElseAction.h"

namespace uking::ai {

SeqIfElseAction::SeqIfElseAction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SeqIfElseAction::~SeqIfElseAction() = default;

bool SeqIfElseAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SeqIfElseAction::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("先行動", params);
}

void SeqIfElseAction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SeqIfElseAction::loadParams_() {
    getStaticParam(&mFailType_s, "FailType");
}

}  // namespace uking::ai
