#include "Game/AI/Action/actionIgniteActorReloadBase.h"

namespace uking::action {

IgniteActorReloadBase::IgniteActorReloadBase(const InitArg& arg) : OnetimeStopASPlay(arg) {}

IgniteActorReloadBase::~IgniteActorReloadBase() = default;

bool IgniteActorReloadBase::init_(sead::Heap* heap) {
    return _48.init(heap);
}

void IgniteActorReloadBase::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
    _48.enter(params);
}

void IgniteActorReloadBase::leave_() {
    _48.leave();
    OnetimeStopASPlay::leave_();
}

void IgniteActorReloadBase::loadParams_() {
    OnetimeStopASPlay::loadParams_();
    _48.loadParams();
}

void IgniteActorReloadBase::calc_() {
    OnetimeStopASPlay::calc_();
    if (isFinished() || isFailed())
        return;
    _48.calc();
}

bool IgniteActorReloadBase::isFailed() const {
    return ActionBase::isFailed() || _48.isFailed();
}

bool IgniteActorReloadBase::isFinished() const {
    return OnetimeStopASPlay::isFinished() && _48.isFinished();
}

}  // namespace uking::action
