#include "Game/AI/AI/aiNPCTalkBalloon.h"
#include "Game/Actor/actNPCBase.h"

namespace uking::ai {

NPCTalkBalloon::NPCTalkBalloon(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
NPCTalkBalloon::~NPCTalkBalloon() {
    ;
}

void NPCTalkBalloon::enter_(ksys::act::ai::InlineParamPack* params) {
    _60 = false;
    const f32 duration = *mDurationTime_s * 30.0f;
    _64 = ksys::Timer(duration, duration);
    const f32 delay = *mDelayFrame_s;
    _70 = ksys::Timer(delay, delay);
    _80 = sead::SafeString();
    if (auto* npc = sead::DynamicCast<act::NPCBase>(mActor))
        _80 = npc->_c18;
    sub_71004E1684();
}

void NPCTalkBalloon::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NPCTalkBalloon::loadParams_() {
    getStaticParam(&mDurationTime_s, "DurationTime");
    getStaticParam(&mDelayFrame_s, "DelayFrame");
    getDynamicParam(&mMessageId_d, "MessageId");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
