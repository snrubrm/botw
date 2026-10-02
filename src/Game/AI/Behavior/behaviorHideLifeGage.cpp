#include "Game/AI/Behavior/behaviorHideLifeGage.h"

namespace uking::behavior {

HideLifeGage::HideLifeGage(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

HideLifeGage::~HideLifeGage() = default;

bool HideLifeGage::m6(sead::Heap* heap) {
    return true;
}

void HideLifeGage::m7() {}

void HideLifeGage::loadParams() {

}

}  // namespace uking::behavior
