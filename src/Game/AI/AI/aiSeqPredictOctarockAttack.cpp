#include "Game/AI/AI/aiSeqPredictOctarockAttack.h"

namespace uking::ai {

SeqPredictOctarockAttack::SeqPredictOctarockAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SeqPredictOctarockAttack::~SeqPredictOctarockAttack() = default;

bool SeqPredictOctarockAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SeqPredictOctarockAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    _4c = *mTargetPos_d;
    _58 = *mTargetVel_d;
    _48 = true;
    sub_7100564154();
}

void SeqPredictOctarockAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SeqPredictOctarockAttack::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetVel_d, "TargetVel");
}

}  // namespace uking::ai
