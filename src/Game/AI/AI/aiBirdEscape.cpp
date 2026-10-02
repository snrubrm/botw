#include "Game/AI/AI/aiBirdEscape.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::ai {

BirdEscape::BirdEscape(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BirdEscape::~BirdEscape() = default;

bool BirdEscape::init_(sead::Heap* heap) {
    auto* root = mActor->getRootAi();
    _74 = (root && root->getI() == 4) || *mIsLocatorCreate_m;
    return true;
}

void BirdEscape::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool BirdEscape::isChangeable() const {
    return false;
}

void BirdEscape::leave_() {
    ksys::act::ai::Ai::leave_();
}

void BirdEscape::loadParams_() {
    getStaticParam(&mForceEndTimer_s, "ForceEndTimer");
    getStaticParam(&mIsUseEscapeBefore_s, "IsUseEscapeBefore");
    getStaticParam(&mIsUseEscapeEnd_s, "IsUseEscapeEnd");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getMapUnitParam(&mIsLocatorCreate_m, "IsLocatorCreate");
}

}  // namespace uking::ai
