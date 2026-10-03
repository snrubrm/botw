#include "Game/AI/Action/actionSwimEnemyAnmBackBlownOff.h"

namespace uking::action {

SwimEnemyAnmBackBlownOff::SwimEnemyAnmBackBlownOff(const InitArg& arg)
    : SwimEnemyAnmBackBlownOffBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
SwimEnemyAnmBackBlownOff::~SwimEnemyAnmBackBlownOff() {
    ;
}

bool SwimEnemyAnmBackBlownOff::init_(sead::Heap* heap) {
    return SwimEnemyAnmBackBlownOffBase::init_(heap);
}

void SwimEnemyAnmBackBlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    SwimEnemyAnmBackBlownOffBase::enter_(params);
}

void SwimEnemyAnmBackBlownOff::leave_() {
    SwimEnemyAnmBackBlownOffBase::leave_();
}

void SwimEnemyAnmBackBlownOff::loadParams_() {
    SwimEnemyAnmBackBlownOffBase::loadParams_();
    getStaticParam(&mRotSpeed_s, "RotSpeed");
}

void SwimEnemyAnmBackBlownOff::calc_() {
    SwimEnemyAnmBackBlownOffBase::calc_();
}

}  // namespace uking::action
