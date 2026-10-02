#include "Game/AI/AI/aiNPCAlert.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceAwareness.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectNpc.h"

namespace uking::ai {

NPCAlert::NPCAlert(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCAlert::~NPCAlert() = default;

bool NPCAlert::init_(sead::Heap* heap) {
    auto* actor = mActor;
    _70 = actor->getParam()->getRes().mAwareness->sight_angle.ref();
    _74 = actor->getParam()->getRes().mGParamList->getNpc()->mIsNotTurnDetect.ref();
    return true;
}

void NPCAlert::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCAlert::loadParams_() {
    getStaticParam(&mMinReactionTime_s, "MinReactionTime");
    getStaticParam(&mReleaseDist_s, "ReleaseDist");
    getDynamicParam(&mTerrorLevel_d, "TerrorLevel");
    getDynamicParam(&mIsTimeOver_d, "IsTimeOver");
    getDynamicParam(&mIsSitting_d, "IsSitting");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTerrorEmitter_d, "TerrorEmitter");
}

}  // namespace uking::ai
