#include "Game/AI/AI/aiAnimalTimelineAI.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

AnimalTimelineAI::AnimalTimelineAI(const InitArg& arg) : TimelineAI(arg) {}

// The SafeString member makes the original keep the vtable store that a defaulted destructor drops;
// written as upstream's GameDataFlagSelector::~GameDataFlagSelector() { ; } (commit 96101229).
AnimalTimelineAI::~AnimalTimelineAI() { ; }

bool AnimalTimelineAI::init_(sead::Heap* heap) {
    if (!TimelineAI::init_(heap))
        return false;
    _48.clear();
    mActor->setFlag(ksys::act::Actor::ActorFlag::_33, true);
    return true;
}

void AnimalTimelineAI::enter_(ksys::act::ai::InlineParamPack* params) {
    if (_48.isEmpty()) {
        TimelineAI::enter_(params);
        return;
    }
    const sead::SafeString& name = m34();
    ksys::act::ai::InlineParamPack pack;
    m36(name, &pack);
    changeChild(name.cstr(), &pack);
}

void AnimalTimelineAI::calc_() {
    TimelineAI::calc_();
}

void AnimalTimelineAI::leave_() {
    TimelineAI::leave_();
}

void AnimalTimelineAI::loadParams_() {
    TimelineAI::loadParams_();
    getAITreeVariable(&mDomesticAnimalRailName_a, "DomesticAnimalRailName");
}

void AnimalTimelineAI::m36(const sead::SafeString& name, ksys::act::ai::InlineParamPack* params) {
    _48 = name;
    static_cast<sead::BufferedSafeString*>(mDomesticAnimalRailName_a)->copy(name);
}

}  // namespace uking::ai
