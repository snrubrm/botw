#include "Game/AI/Action/actionEventSetEnableGrass.h"
#include "KingSystem/Terrain/teraSystem.h"

namespace uking::action {

EventSetEnableGrass::EventSetEnableGrass(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventSetEnableGrass::~EventSetEnableGrass() = default;

bool EventSetEnableGrass::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool EventSetEnableGrass::oneShot_() {
    auto* terrain = ksys::tera::Terrain::instance();
    if (terrain && terrain->isGrassEnabled())
        terrain->sub_710114DE4C()->sub_7101150990(*mEnable_d);
    return true;
}

void EventSetEnableGrass::loadParams_() {
    getDynamicParam(&mEnable_d, "Enable");
}

}  // namespace uking::action
