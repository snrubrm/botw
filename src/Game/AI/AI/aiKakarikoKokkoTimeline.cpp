#include "Game/AI/AI/aiKakarikoKokkoTimeline.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actSchedule.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"

namespace uking::ai {

KakarikoKokkoTimeline::KakarikoKokkoTimeline(const InitArg& arg) : AnimalTimelineAI(arg) {}

// The SafeString members make the original keep the vtable store that a defaulted destructor drops;
// written as upstream's GameDataFlagSelector::~GameDataFlagSelector() { ; } (commit 96101229).
KakarikoKokkoTimeline::~KakarikoKokkoTimeline() { ; }

bool KakarikoKokkoTimeline::init_(sead::Heap* heap) {
    if (!AnimalTimelineAI::init_(heap))
        return false;
    if (auto* schedule = mActor->getSchedule()) {
        schedule->_2f8 |= 2;
        sub_7100450D14();
        return true;
    }
    return false;
}

const sead::SafeString& KakarikoKokkoTimeline::m34() {
    return _c0;
}

void KakarikoKokkoTimeline::sub_7100450D14() {
    auto* schedule = mActor->getSchedule();
    if (!schedule)
        return;

    if (!mCheckGatheredFlagName_m.isEmpty() &&
        (mEndForceChangeFlagName_s.isEmpty() || !ksys::gdt::getBoolByKey(mEndForceChangeFlagName_s)) &&
        !mStartForceChangeFlagName_s.isEmpty() &&
        ksys::gdt::getBoolByKey(mStartForceChangeFlagName_s) &&
        ksys::gdt::getBoolByKey(mCheckGatheredFlagName_m)) {
        _c0 = mForceChangeChildKeyName_s;
        schedule->_88 = _c0;
    } else {
        _c0 = TimelineAI::m34();
        schedule->_88 = sead::SafeString("");
    }
}

void KakarikoKokkoTimeline::enter_(ksys::act::ai::InlineParamPack* params) {
    AnimalTimelineAI::enter_(params);
}

void KakarikoKokkoTimeline::calc_() {
    sub_7100450D14();
    AnimalTimelineAI::calc_();
}

void KakarikoKokkoTimeline::leave_() {
    AnimalTimelineAI::leave_();
}

void KakarikoKokkoTimeline::loadParams_() {
    AnimalTimelineAI::loadParams_();
    getStaticParam(&mForceChangeChildKeyName_s, "ForceChangeChildKeyName");
    getStaticParam(&mStartForceChangeFlagName_s, "StartForceChangeFlagName");
    getStaticParam(&mEndForceChangeFlagName_s, "EndForceChangeFlagName");
    getMapUnitParam(&mCheckGatheredFlagName_m, "CheckGatheredFlagName");
}

}  // namespace uking::ai
