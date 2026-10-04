#include "Game/AI/Action/actionForceEndPlayerSlow.h"
#include "KingSystem/System/VFR.h"

// Declaration-only helper; its original source namespace is unknown.
bool fadeSlowEffect();

namespace uking::action {

ForceEndPlayerSlow::ForceEndPlayerSlow(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForceEndPlayerSlow::~ForceEndPlayerSlow() = default;

bool ForceEndPlayerSlow::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForceEndPlayerSlow::loadParams_() {}

bool ForceEndPlayerSlow::oneShot_() {
    if (auto* vfr = ksys::VFR::instance()) {
        vfr->resetTimeMultiplier(0);
        vfr->resetTimeMultiplier(1);
        vfr->resetTimeMultiplier(2);
    }
    fadeSlowEffect();
    return true;
}

}  // namespace uking::action
