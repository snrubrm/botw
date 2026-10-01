#include "Game/AI/AI/aiSeqNextMessage.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/System/Timer.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

SeqNextMessage::SeqNextMessage(const InitArg& arg) : SeqTwoAction(arg) {}

SeqNextMessage::~SeqNextMessage() = default;

bool SeqNextMessage::init_(sead::Heap* heap) {
    return SeqTwoAction::init_(heap);
}

void SeqNextMessage::enter_(ksys::act::ai::InlineParamPack* params) {
    SeqTwoAction::enter_(params);
    const int max_time = *mDelayTimeMax_s;
    _94 = sead::Mathi::min(0, max_time);
    _98 = sead::Mathi::max(0, max_time);
    _58.x();
    s32 time = _94;
    if (_98 != _94)
        time = sead::GlobalRandom::instance()->getS32Range(_94, _98);
    _90 = time;
    _9c = false;
}

void SeqNextMessage::calc_() {
    SeqTwoAction::calc_();
    if (_9c) {
        ksys::Timer::update(&_90, -1.0f);
        return;
    }
    if (_58._30)
        _9c = true;
}

void SeqNextMessage::leave_() {
    SeqTwoAction::leave_();
}

void SeqNextMessage::loadParams_() {
    SeqTwoAction::loadParams_();
    getStaticParam(&mDelayTimeMax_s, "DelayTimeMax");
}

bool SeqNextMessage::m35() const {
    return getCurrentChild()->isChangeable() && _90 < 0.0f;
}

// NON_MATCHING: regalloc (the original keeps &_58 in x20 for the inlined x())
bool SeqNextMessage::handleMessage_(const ksys::Message& message) {
    if (_58.m2(message)) {
        if (isCurrentChild("先行動"))
            return true;
        _58.x();
    }
    return false;
}

}  // namespace uking::ai

bool Unk_710241d7c8::m2(const ksys::Message& message) {
    if (message.getType().value != 0x80000a6)
        return false;

    _30 = true;
    _18 = message.getSource();
    return true;
}
