#include "Game/AI/AI/aiNPCConfront.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectNpc.h"

namespace uking::ai {

NPCConfront::NPCConfront(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCConfront::~NPCConfront() = default;

bool NPCConfront::init_(sead::Heap* heap) {
    auto* actor = mActor;
    _90 = actor->getParam()->getRes().mGParamList->getNpc()->mIsNotTurnDetect.ref();
    if (auto* npc = sead::DynamicCast<act::NPC>(actor))
        npc->_fe8 |= 4;
    return true;
}

void NPCConfront::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCConfront::leave_() {
    sub_71005D7518(mActor, true);
}

void NPCConfront::loadParams_() {
    getStaticParam(&mCounterGuardCount_s, "CounterGuardCount");
    getStaticParam(&mReleaseDistance_s, "ReleaseDistance");
    getStaticParam(&mReleaseTime_s, "ReleaseTime");
    getStaticParam(&mCounterRate_s, "CounterRate");
    getStaticParam(&mDirectTurnAngle_s, "DirectTurnAngle");
    getDynamicParam(&mTerrorLevel_d, "TerrorLevel");
    getDynamicParam(&mIsTimeOver_d, "IsTimeOver");
    getDynamicParam(&mIsSitting_d, "IsSitting");
    getDynamicParam(&mIsNeedUnEquipWeapon_d, "IsNeedUnEquipWeapon");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTerrorEmitter_d, "TerrorEmitter");
}

}  // namespace uking::ai
