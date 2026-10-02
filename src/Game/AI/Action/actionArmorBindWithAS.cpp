#include "Game/AI/Action/actionArmorBindWithAS.h"

namespace uking::action {

ArmorBindWithAS::ArmorBindWithAS(const InitArg& arg) : ArmorBindAction(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
ArmorBindWithAS::~ArmorBindWithAS() {
    ;
}

void ArmorBindWithAS::enter_(ksys::act::ai::InlineParamPack* params) {
    ArmorBindAction::enter_(params);
}

void ArmorBindWithAS::leave_() {
    ArmorBindAction::leave_();
}

void ArmorBindWithAS::loadParams_() {
    ArmorBindAction::loadParams_();
    getDynamicParam(&mASName_d, "ASName");
}

}  // namespace uking::action
