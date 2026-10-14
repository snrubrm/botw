#include "Game/Actor/Action/actionStoppingAttackBase.h"

namespace uking::action {

StoppingAttackBase::StoppingAttackBase(const InitArg& arg) : StopBase(arg) {}

StoppingAttackBase::~StoppingAttackBase() = default;

bool StoppingAttackBase::init_(sead::Heap* heap) {
    return m32()->init(heap);
}

void StoppingAttackBase::enter_(ksys::act::ai::InlineParamPack* params) {
    m32()->enter(params);
    StopBase::enter_(params);
}

void StoppingAttackBase::leave_() {
    StopBase::leave_();
    m32()->leave();
}

void StoppingAttackBase::loadParams_() {
    StopBase::loadParams_();
    m32()->loadParams();
}

void StoppingAttackBase::calc_() {
    StopBase::calc_();
    m32()->calc();
}

}  // namespace uking::action
