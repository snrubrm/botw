#include "Game/AI/AI/aiFishRoot.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

FishRoot::FishRoot(const InitArg& arg) : SimpleWildlifeRoot(arg) {}

FishRoot::~FishRoot() = default;

bool FishRoot::init_(sead::Heap* heap) {
    return SimpleWildlifeRoot::init_(heap);
}

void FishRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    SimpleWildlifeRoot::enter_(params);
}

void FishRoot::leave_() {
    SimpleWildlifeRoot::leave_();
}

void FishRoot::loadParams_() {
    SimpleWildlifeRoot::loadParams_();
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mOnGroundDepth_s, "OnGroundDepth");
    getStaticParam(&mNextJumpTimeBase_s, "NextJumpTimeBase");
    getStaticParam(&mNextJumpTimeRand_s, "NextJumpTimeRand");
    getStaticParam(&mAllowReturnThreatDist_s, "AllowReturnThreatDist");
    getStaticParam(&mFrameUntilOutOfWater_s, "FrameUntilOutOfWater");
    getStaticParam(&mDistRunFromPlayerOnReturn_s, "DistRunFromPlayerOnReturn");
    getStaticParam(&mIgnoreFoodBase_s, "IgnoreFoodBase");
    getStaticParam(&mIgnoreFoodRand_s, "IgnoreFoodRand");
    getStaticParam(&mIgnoreFoodAfterSuccessBase_s, "IgnoreFoodAfterSuccessBase");
    getStaticParam(&mIgnoreFoodAfterSuccessRand_s, "IgnoreFoodAfterSuccessRand");
}

bool FishRoot::m34() {
    return SimpleWildlifeRoot::m34();
}

bool FishRoot::m36() {
    return false;
}

void FishRoot::m40() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F60604();
    SimpleWildlifeRoot::m40();
}

}  // namespace uking::ai
