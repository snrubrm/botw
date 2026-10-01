#include "Game/AI/Action/actionOnMUAssignSaveForUsed.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

OnMUAssignSaveForUsed::OnMUAssignSaveForUsed(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OnMUAssignSaveForUsed::~OnMUAssignSaveForUsed() = default;

bool OnMUAssignSaveForUsed::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool OnMUAssignSaveForUsed::oneShot_() {
    mActor->setRevivalFlagForUsed(true);
    return true;
}

void OnMUAssignSaveForUsed::loadParams_() {}

}  // namespace uking::action
