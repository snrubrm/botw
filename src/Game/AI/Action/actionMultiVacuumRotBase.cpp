#include "Game/AI/Action/actionMultiVacuumRotBase.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

MultiVacuumRotBase::MultiVacuumRotBase(const InitArg& arg)
    : MultiVacuumBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
MultiVacuumRotBase::~MultiVacuumRotBase() {
    ;
}

bool MultiVacuumRotBase::init_(sead::Heap* heap) {
    return MultiVacuumBase::init_(heap);
}

void MultiVacuumRotBase::enter_(ksys::act::ai::InlineParamPack* params) {
    MultiVacuumBase::enter_(params);
    sub_710073FA90(&_1d8, mActor);
    _1fc = mActor->getAngVelocity().length();
}

void MultiVacuumRotBase::leave_() {
    MultiVacuumBase::leave_();
}

void MultiVacuumRotBase::loadParams_() {
    MultiVacuumBase::loadParams_();
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void MultiVacuumRotBase::calc_() {
    MultiVacuumBase::calc_();
}

}  // namespace uking::action
