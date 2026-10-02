#include "Game/AI/Behavior/behaviorOctarockHideForm.h"

namespace uking::behavior {

OctarockHideForm::OctarockHideForm(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

OctarockHideForm::~OctarockHideForm() = default;

bool OctarockHideForm::m6(sead::Heap* heap) {
    return true;
}

void OctarockHideForm::m8() {}

void OctarockHideForm::loadParams() {
    getAITreeVariable(&mOctarockFormChangeUnit_a, "OctarockFormChangeUnit");
}

}  // namespace uking::behavior
