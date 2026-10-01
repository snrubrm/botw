#include "Game/AI/AI/aiSeqTimeredPlusRandomTwoAction.h"
#include <random/seadGlobalRandom.h>

namespace uking::ai {

SeqTimeredPlusRandomTwoAction::SeqTimeredPlusRandomTwoAction(const InitArg& arg)
    : SeqTimeredTwoAction(arg) {}

SeqTimeredPlusRandomTwoAction::~SeqTimeredPlusRandomTwoAction() = default;

bool SeqTimeredPlusRandomTwoAction::init_(sead::Heap* heap) {
    return SeqTimeredTwoAction::init_(heap);
}

void SeqTimeredPlusRandomTwoAction::enter_(ksys::act::ai::InlineParamPack* params) {
    SeqTimeredTwoAction::enter_(params);
}

void SeqTimeredPlusRandomTwoAction::leave_() {
    SeqTimeredTwoAction::leave_();
}

void SeqTimeredPlusRandomTwoAction::loadParams_() {
    SeqTimeredTwoAction::loadParams_();
    getStaticParam(&mFirstActionRandMax_s, "FirstActionRandMax");
    getStaticParam(&mSecondActionRandMax_s, "SecondActionRandMax");
}

void SeqTimeredPlusRandomTwoAction::calc_() {
    SeqTimeredTwoAction::calc_();
}

int SeqTimeredPlusRandomTwoAction::m34() {
    return f32(*mFirstActionTime_s) +
           f32(*mFirstActionRandMax_s) * sead::GlobalRandom::instance()->getF32();
}

int SeqTimeredPlusRandomTwoAction::m35() {
    return f32(*mSecondActionTime_s) +
           f32(*mSecondActionRandMax_s) * sead::GlobalRandom::instance()->getF32();
}

}  // namespace uking::ai
