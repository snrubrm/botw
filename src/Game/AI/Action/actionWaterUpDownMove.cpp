#include "Game/AI/Action/actionWaterUpDownMove.h"

namespace uking::action {

WaterUpDownMove::WaterUpDownMove(const InitArg& arg) : WaterUpDownMoveBase(arg) {}

WaterUpDownMove::~WaterUpDownMove() = default;

bool WaterUpDownMove::init_(sead::Heap* heap) {
    return WaterUpDownMoveBase::init_(heap);
}

void WaterUpDownMove::enter_(ksys::act::ai::InlineParamPack* params) {
    WaterUpDownMoveBase::enter_(params);
    _6c = *mStartDepth_s;
}

void WaterUpDownMove::leave_() {
    WaterUpDownMoveBase::leave_();
}

void WaterUpDownMove::loadParams_() {
    WaterUpDownMoveBase::loadParams_();
    getStaticParam(&mStartDepth_s, "StartDepth");
    getStaticParam(&mTargetDepth_s, "TargetDepth");
}

void WaterUpDownMove::calc_() {
    WaterUpDownMoveBase::calc_();
}

void WaterUpDownMove::m32(ksys::as::ASList::Unk4* query) {
    sub_71002B390C(*mTargetDepth_s, query->_10);
}

}  // namespace uking::action
