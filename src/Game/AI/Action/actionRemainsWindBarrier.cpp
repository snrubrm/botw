#include "Game/AI/Action/actionRemainsWindBarrier.h"

namespace uking::action {

RemainsWindBarrier::RemainsWindBarrier(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RemainsWindBarrier::~RemainsWindBarrier() {
    if (_30) {
        delete _30;
        _30 = nullptr;
    }
}

bool RemainsWindBarrier::init_(sead::Heap* heap) {
    _30 = new (heap) ksys::act::ModelBindInfo;
    return true;
}

void RemainsWindBarrier::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void RemainsWindBarrier::leave_() {
    ksys::act::ai::Action::leave_();
}

void RemainsWindBarrier::loadParams_() {}

void RemainsWindBarrier::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
