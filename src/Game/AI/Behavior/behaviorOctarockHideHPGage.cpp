#include "Game/AI/Behavior/behaviorOctarockHideHPGage.h"

namespace uking::behavior {

OctarockHideHPGage::OctarockHideHPGage(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

OctarockHideHPGage::~OctarockHideHPGage() = default;

bool OctarockHideHPGage::m6(sead::Heap* heap) {
    return true;
}

void OctarockHideHPGage::m8() {}

void OctarockHideHPGage::loadParams() {
    getAITreeVariable(&mOctarockFormChangeUnit_a, "OctarockFormChangeUnit");
}

}  // namespace uking::behavior
