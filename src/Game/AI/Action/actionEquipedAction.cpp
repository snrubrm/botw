#include "Game/AI/Action/actionEquipedAction.h"

namespace uking::action {

EquipedAction::EquipedAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

void EquipedAction::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    m32();
    m34();
}

void EquipedAction::leave_() {
    m35();
}

void EquipedAction::loadParams_() {
    getDynamicParam(&mNodeName_d, "NodeName");
    getDynamicParam(&mRotOffset_d, "RotOffset");
    getDynamicParam(&mTransOffset_d, "TransOffset");
}

void EquipedAction::calc_() {
    ksys::act::ai::Action::calc_();
}

void EquipedAction::m32() {}

}  // namespace uking::action
