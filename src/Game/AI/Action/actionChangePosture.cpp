#include "Game/AI/Action/actionChangePosture.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::action {

ChangePosture::ChangePosture(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ChangePosture::~ChangePosture() = default;

bool ChangePosture::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ChangePosture::loadParams_() {
    getDynamicParam(&mPosture_d, "Posture");
}

bool ChangePosture::oneShot_() {
    mActor->getASList()->goLimpFromHeadShotMaybe(0x3b, mPosture_d, 0);
    return true;
}

}  // namespace uking::action
