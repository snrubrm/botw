#include "Game/AI/Action/actionAttackBase.h"

namespace uking::action {

AttackBase::AttackBase(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

AttackBase::~AttackBase() = default;

bool AttackBase::init_(sead::Heap* heap) {
    return m32()->init(heap);
}

void AttackBase::enter_(ksys::act::ai::InlineParamPack* params) {
    m32()->enter(params);
    ActionWithPosAngReduce::enter_(params);
}

void AttackBase::leave_() {
    ActionWithPosAngReduce::leave_();
    m32()->leave();
}

void AttackBase::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    m32()->loadParams();
}

void AttackBase::calc_() {
    ActionWithPosAngReduce::calc_();
    m32()->calc();
}

}  // namespace uking::action
