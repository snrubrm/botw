#include "Game/AI/AI/aiPrevASSkipSeq.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

PrevASSkipSeq::PrevASSkipSeq(const InitArg& arg) : SeqTwoAction(arg) {}

PrevASSkipSeq::~PrevASSkipSeq() = default;

bool PrevASSkipSeq::init_(sead::Heap* heap) {
    return SeqTwoAction::init_(heap);
}

void PrevASSkipSeq::enter_(ksys::act::ai::InlineParamPack* params) {
    SeqTwoAction::enter_(params);
}

void PrevASSkipSeq::calc_() {
    SeqTwoAction::calc_();
}

void PrevASSkipSeq::leave_() {
    SeqTwoAction::leave_();
}

void PrevASSkipSeq::loadParams_() {
    SeqTwoAction::loadParams_();
    getStaticParam(&mPrevASName_s, "PrevASName");
}

bool PrevASSkipSeq::m36() const {
    return mActor->getASList()->x_1(0, 0) == mPrevASName_s;
}

}  // namespace uking::ai
