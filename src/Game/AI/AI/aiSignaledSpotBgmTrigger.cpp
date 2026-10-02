#include "Game/AI/AI/aiSignaledSpotBgmTrigger.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

SignaledSpotBgmTrigger::SignaledSpotBgmTrigger(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
SignaledSpotBgmTrigger::~SignaledSpotBgmTrigger() {
    ;
}

bool SignaledSpotBgmTrigger::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SignaledSpotBgmTrigger::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("待機");
}

void SignaledSpotBgmTrigger::calc_() {
    const bool on = mActor->checkBasicSig();
    if (_50 == on)
        return;

    if (on) {
        ksys::act::ai::InlineParamPack child_params;
        child_params.addInt(0, "SoundDelay", -1);
        child_params.addString(mSound_m, "Sound", -1);
        child_params.addString("SpotBgm", "SLinkInst", -1);
        changeChild("再生", &child_params);
    } else {
        changeChild("待機");
    }
    _50 = on;
}

void SignaledSpotBgmTrigger::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SignaledSpotBgmTrigger::loadParams_() {
    getMapUnitParam(&mIsStopWithoutReductionY_m, "IsStopWithoutReductionY");
    getMapUnitParam(&mSound_m, "Sound");
}

}  // namespace uking::ai
