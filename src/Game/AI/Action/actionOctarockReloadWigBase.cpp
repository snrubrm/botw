#include "Game/AI/Action/actionOctarockReloadWigBase.h"

namespace uking::action {

OctarockReloadWigBase::OctarockReloadWigBase(const InitArg& arg) : OnetimeStopASPlay(arg) {}

OctarockReloadWigBase::~OctarockReloadWigBase() = default;

bool OctarockReloadWigBase::init_(sead::Heap* heap) {
    return _48.init(heap);
}

void OctarockReloadWigBase::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
    _48.enter(params);
}

void OctarockReloadWigBase::leave_() {
    _48.leave();
    OnetimeStopASPlay::leave_();
}

void OctarockReloadWigBase::loadParams_() {
    OnetimeStopASPlay::loadParams_();
    _48.loadParams();
}

void OctarockReloadWigBase::calc_() {
    OnetimeStopASPlay::calc_();
    if (isFinished() || isFailed())
        return;
    _48.calc();
}

bool OctarockReloadWigBase::isFailed() const {
    return ActionBase::isFailed() || _48.isFailed();
}

bool OctarockReloadWigBase::isFinished() const {
    return OnetimeStopASPlay::isFinished() && _48.isFinished();
}

}  // namespace uking::action
