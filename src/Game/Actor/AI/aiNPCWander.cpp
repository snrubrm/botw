#include "Game/Actor/AI/aiNPCWander.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actSchedule.h"
#include "Game/Actor/aiUnk_7100711020.h"
#include "KingSystem/Map/mapRail.h"
#include <math/seadMathCalcCommon.h>

namespace uking::ai {

NPCWander::NPCWander(const InitArg& arg) : NPCScheduleMove(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
NPCWander::~NPCWander() {
    ;
}

bool NPCWander::init_(sead::Heap* heap) {
    if (!NPCScheduleMove::init_(heap))
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
    NPCScheduleMove::enter_(params);
}

void NPCWander::leave_() {
    NPCScheduleMove::leave_();
}

void NPCWander::loadParams_() {
    NPCScheduleMove::loadParams_();
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
// NON_MATCHING: only the registers of the two velocity components differ (s9 / s8 swapped)
// 0x71004e9ff8
bool NPCWander::sub_71004E9FF8() {
    const sead::Vector3f& velocity = mActor->getASList()->sub_710115D2D4();
    f32 x = velocity.x;
    f32 z = velocity.z;
    if (mActor->sub_71011C7A98()) {
        x *= mActor->get830();
        z *= mActor->get830();
    }
    f32 length = sead::Mathf::sqrt(x * x + z * z);
    if (length < sead::Mathf::epsilon())
        length = 0.05f;
    _e8->x(length * *mRailUpdateDistRate_s);

    if (_e8->_8.rail->isClosed())
        return false;
    const f32 progress = _e8->_30.progress;
    if (progress != 0.0f && progress != f32(_e8->_8.rail->getNumPoints()) - 1.0f)
        return false;
    _e8->sub_7100EEBE9C(-_e8->_58);
    return true;
}

// 0x71004e8014
void NPCWander::sub_71004E8014(bool a1, bool a2) {
    auto* npc = sead::DynamicCast<act::NPC>(mActor);
    auto* schedule = mActor->getSchedule();
    if (npc && schedule) {
        sead::SafeString as_name;
        if (a2)
            as_name = schedule->_238;
        else
            as_name = a1 ? schedule->_218 : schedule->_228;

        if (as_name == "Hold") {
            npc->_1060 = 0;
            sub_7100712E00(mActor);
        } else if (as_name == "Equip") {
            npc->_1060 = 1;
            mActor->getASList()->goLimpFromHeadShotMaybe(44, "", 0);
        } else if (as_name == "Invisible") {
            npc->_1060 = 2;
            mActor->getASList()->goLimpFromHeadShotMaybe(44, "", 0);
        }
    }
}

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
