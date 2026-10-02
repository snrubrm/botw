#include "Game/AI/Action/actionForkIgniteCarriedActor.h"

namespace uking::action {

ForkIgniteCarriedActor::ForkIgniteCarriedActor(const InitArg& arg) : Fork(arg) {}

ForkIgniteCarriedActor::~ForkIgniteCarriedActor() = default;

bool ForkIgniteCarriedActor::init_(sead::Heap* heap) {
    if (!Fork::init_(heap))
        return false;
    return _30.init(heap);
}

void ForkIgniteCarriedActor::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
    _30.enter(params);
}

void ForkIgniteCarriedActor::leave_() {
    _30.leave();
    Fork::leave_();
}

void ForkIgniteCarriedActor::loadParams_() {
    Fork::loadParams_();
    _30.loadParams();
}

void ForkIgniteCarriedActor::calc_() {
    Fork::calc_();
    _30.calc();
    if (_30.isFinished())
        setEndState();
    else if (_30.isFailed())
        setFailed();
}

}  // namespace uking::action
