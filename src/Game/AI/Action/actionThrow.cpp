#include "Game/AI/Action/actionThrow.h"

namespace uking::action {

Throw::Throw(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

Throw::~Throw() = default;

bool Throw::init_(sead::Heap* heap) {
    return ActionWithPosAngReduce::init_(heap);
}

void Throw::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
    m32();
    mFlags.reset(Flag::Changeable);
    _30.enter(params);
}

void Throw::leave_() {
    ActionWithPosAngReduce::leave_();
}

void Throw::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    _30.loadParams();
}

void Throw::calc_() {
    ActionWithPosAngReduce::calc_();
    _30.calc();
    if (isFinishedAS(0, 0))
        setFinished();
}

void Throw::m32() {
    playAS("Throw", false, 0, 0, -1.0f);
}

}  // namespace uking::action
