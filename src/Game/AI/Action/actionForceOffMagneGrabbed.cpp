#include "Game/AI/Action/actionForceOffMagneGrabbed.h"
#include "Game/gameSceneSubsysMisc.h"

namespace uking::action {

ForceOffMagneGrabbed::ForceOffMagneGrabbed(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForceOffMagneGrabbed::~ForceOffMagneGrabbed() = default;

bool ForceOffMagneGrabbed::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool ForceOffMagneGrabbed::oneShot_() {
    if (auto* scene = GameSceneSubsys5::instance())
        scene->sub_7100905C8C();
    return true;
}

void ForceOffMagneGrabbed::loadParams_() {}

}  // namespace uking::action
