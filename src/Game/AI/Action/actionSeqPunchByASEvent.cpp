#include "Game/AI/Action/actionSeqPunchByASEvent.h"

namespace uking::action {

SeqPunchByASEvent::SeqPunchByASEvent(const InitArg& arg) : ActionWithAS(arg) {}

SeqPunchByASEvent::~SeqPunchByASEvent() = default;

bool SeqPunchByASEvent::init_(sead::Heap* heap) {
    return ActionWithAS::init_(heap);
}

void SeqPunchByASEvent::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithAS::enter_(params);
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    _50._8 = m32();
    _50._10 = m33();
}

void SeqPunchByASEvent::leave_() {
    ActionWithAS::leave_();
    _50.sub_7100720FD0();
}

// NON_MATCHING: regalloc only (the original computes `this + 0x30` into a callee-saved register before the first
// getStaticParam call).
void SeqPunchByASEvent::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mAttackIntensity_s, "AttackIntensity");
    getStaticParam(&mIsHammer_s, "IsHammer");
    getStaticParam(&mASName_s, "ASName");
}

void SeqPunchByASEvent::calc_() {
    ActionWithAS::calc_();
    _50.sub_7100720B28();
}

}  // namespace uking::action
