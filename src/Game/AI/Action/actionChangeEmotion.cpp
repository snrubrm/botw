#include "Game/AI/Action/actionChangeEmotion.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::action {

ChangeEmotion::ChangeEmotion(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ChangeEmotion::~ChangeEmotion() = default;

bool ChangeEmotion::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ChangeEmotion::loadParams_() {
    getDynamicParam(&mIsOnlyFace_d, "IsOnlyFace");
    getDynamicParam(&mEmotionType_d, "EmotionType");
}

bool ChangeEmotion::oneShot_() {
    if (!*mIsOnlyFace_d)
        mActor->getASList()->goLimpFromHeadShotMaybe(0x37, mEmotionType_d, 0);
    mActor->getASList()->goLimpFromHeadShotMaybe(0x38, mEmotionType_d, 0);
    return true;
}

}  // namespace uking::action
