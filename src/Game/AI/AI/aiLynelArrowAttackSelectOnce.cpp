#include "Game/AI/AI/aiLynelArrowAttackSelectOnce.h"

namespace uking::ai {

LynelArrowAttackSelectOnce::LynelArrowAttackSelectOnce(const InitArg& arg)
    : LynelArrowAttackSelectBase(arg) {}

LynelArrowAttackSelectOnce::~LynelArrowAttackSelectOnce() = default;

bool LynelArrowAttackSelectOnce::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool LynelArrowAttackSelectOnce::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool LynelArrowAttackSelectOnce::init_(sead::Heap* heap) {
    return LynelArrowAttackSelectBase::init_(heap);
}

void LynelArrowAttackSelectOnce::enter_(ksys::act::ai::InlineParamPack* params) {
    LynelArrowAttackSelectBase::enter_(params);
}

void LynelArrowAttackSelectOnce::calc_() {
    LynelArrowAttackSelectBase::calc_();
}

void LynelArrowAttackSelectOnce::leave_() {
    LynelArrowAttackSelectBase::leave_();
}

void LynelArrowAttackSelectOnce::loadParams_() {
    LynelArrowAttackSelectBase::loadParams_();
}

}  // namespace uking::ai
