#include "Game/AI/Action/actionGiantPunchAttack.h"

namespace uking::action {

GiantPunchAttack::GiantPunchAttack(const InitArg& arg) : PunchAttack(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
GiantPunchAttack::~GiantPunchAttack() {
    ;
}

bool GiantPunchAttack::init_(sead::Heap* heap) {
    return PunchAttack::init_(heap);
}

void GiantPunchAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    PunchAttack::enter_(params);
    _e0 = false;
}

void GiantPunchAttack::leave_() {
    PunchAttack::leave_();
}

void GiantPunchAttack::loadParams_() {
    PunchAttack::loadParams_();
    getStaticParam(&mCoBodyName_s, "CoBodyName");
}

void GiantPunchAttack::calc_() {
    PunchAttack::calc_();
    m32();
}

}  // namespace uking::action
