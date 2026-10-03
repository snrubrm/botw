#include "Game/AI/AI/aiGuardianMiniGroggy.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

GuardianMiniGroggy::GuardianMiniGroggy(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The SafeString member makes the original keep the vtable store (see AssassinCallSelect).
GuardianMiniGroggy::~GuardianMiniGroggy() { ; }

void GuardianMiniGroggy::enter_(ksys::act::ai::InlineParamPack* params) {
    _75 = false;
    mActor->getASList()->startAnimationMaybe(-1.0f, -1.0f, "GroggyLoop", 1, 0, true);
    _68 = ksys::Timer(*mChanceTime_s, *mChanceTime_s);
    changeChild("チャンス", params);
}

void GuardianMiniGroggy::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GuardianMiniGroggy::loadParams_() {
    getStaticParam(&mChanceTime_s, "ChanceTime");
    getStaticParam(&mRestartASName_s, "RestartASName");
    getStaticParam(&mDefaultASName_s, "DefaultASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
