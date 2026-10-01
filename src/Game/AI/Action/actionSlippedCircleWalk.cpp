#include "Game/AI/Action/actionSlippedCircleWalk.h"

namespace uking::action {

SlippedCircleWalk::SlippedCircleWalk(const InitArg& arg) : SlippedCircleWalkBase(arg) {}

SlippedCircleWalk::~SlippedCircleWalk() = default;

bool SlippedCircleWalk::init_(sead::Heap* heap) {
    return SlippedCircleWalkBase::init_(heap);
}

void SlippedCircleWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    SlippedCircleWalkBase::enter_(params);
    playAS(mASName_s.cstr(), true, 0, 0, -1.0f);
}

void SlippedCircleWalk::leave_() {
    SlippedCircleWalkBase::leave_();
}

void SlippedCircleWalk::loadParams_() {
    SlippedCircleWalkBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void SlippedCircleWalk::calc_() {
    SlippedCircleWalkBase::calc_();
}

}  // namespace uking::action
