#include "Game/AI/Behavior/behaviorSetInfRotSpeedToSpineController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBoneControl.h"

namespace uking::behavior {

SetInfRotSpeedToSpineController::SetInfRotSpeedToSpineController(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

SetInfRotSpeedToSpineController::~SetInfRotSpeedToSpineController() = default;

bool SetInfRotSpeedToSpineController::m6(sead::Heap* heap) {
    return true;
}

void SetInfRotSpeedToSpineController::m7() {}

void SetInfRotSpeedToSpineController::m8() {
    if (auto* unit = ksys::act::sub_7100D82FFC(mActor->getBoneControl())) {
        unit->sub_7100D8AA60(*mRotSpeed_s);
        unit->sub_7100D8AA08(*mRotSpeed_s);
        unit->sub_7100D8A9D0(1.0f);
    }
}

void SetInfRotSpeedToSpineController::m9() {
    if (auto* unit = ksys::act::sub_7100D82FFC(mActor->getBoneControl())) {
        unit->sub_7100D8AB00();
        unit->sub_7100D8AAB8();
        unit->_9c = unit->_98;
    }
}

void SetInfRotSpeedToSpineController::loadParams() {
    getStaticParam(&mRotSpeed_s, "RotSpeed");
}

}  // namespace uking::behavior
