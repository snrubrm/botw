#include "Game/AI/Action/actionGiantAttackWithAS.h"

namespace uking::action {

GiantAttackWithAS::GiantAttackWithAS(const InitArg& arg) : GiantAttack(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
GiantAttackWithAS::~GiantAttackWithAS() {
    ;
}

bool GiantAttackWithAS::init_(sead::Heap* heap) {
    return GiantAttack::init_(heap);
}

void GiantAttackWithAS::enter_(ksys::act::ai::InlineParamPack* params) {
    GiantAttack::enter_(params);
}

void GiantAttackWithAS::leave_() {
    GiantAttack::leave_();
}

void GiantAttackWithAS::loadParams_() {
    GiantAttack::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void GiantAttackWithAS::calc_() {
    GiantAttack::calc_();
}

void GiantAttackWithAS::m32(const sead::SafeString* name) {}

void GiantAttackWithAS::m33() {}

}  // namespace uking::action
