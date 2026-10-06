#include "Game/AI/AI/aiNPCWander.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

NPCWander::NPCWander(const InitArg& arg) : NPCTravelBase(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
NPCWander::~NPCWander() {
    ;
}

bool NPCWander::init_(sead::Heap* heap) {
    if (!NPCTravelBase::init_(heap))
        return false;

    if (auto* npc = sead::DynamicCast<act::NPC>(mActor)) {
        _d8 = npc;
        _e8 = &npc->_848;
    } else {
        _d8 = nullptr;
    }
    return true;
}

void NPCWander::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCTravelBase::enter_(params);
}

void NPCWander::leave_() {
    NPCTravelBase::leave_();
}

void NPCWander::loadParams_() {
    NPCTravelBase::loadParams_();
    getStaticParam(&mRainWaitTime_s, "RainWaitTime");
    getStaticParam(&mGoalDistance_s, "GoalDistance");
    getStaticParam(&mRailUpdateDistRate_s, "RailUpdateDistRate");
    getStaticParam(&mRainDestination_s, "RainDestination");
    getStaticParam(&mNormalASKeyName_s, "NormalASKeyName");
    getStaticParam(&mRainASKeyName_s, "RainASKeyName");
    getStaticParam(&mRailUniqueName_s, "RailUniqueName");
    getDynamicParam(&mIsPathRest_d, "IsPathRest");
}

// 0x71004ea108
void NPCWander::sub_71004EA108() {
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f pos = mActor->getMtx().getTranslation();
    pack.addVec3(pos, "TargetPos", -1);
    pack.addVec3(_120, "TargetRot", -1);
    changeChild("振り向く", &pack);
}

// 0x71004ea4b0
void NPCWander::sub_71004EA4B0() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_114, "TargetPos", -1);
    pack.addString(_f0, "DynASKeyName", -1);
    changeChild("レール点に移動", &pack);
}

}  // namespace uking::ai
