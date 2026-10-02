#include "Game/AI/AI/aiNPCAttentionAI.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceAwareness.h"

namespace uking::ai {

NPCAttentionAI::NPCAttentionAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCAttentionAI::~NPCAttentionAI() = default;

bool NPCAttentionAI::init_(sead::Heap* heap) {
    _74 = *mIsUseSight_s ? mActor->getParam()->getRes().mAwareness->sight_angle.ref() :
                           *mTurnAngleDiff_s;
    return true;
}

void NPCAttentionAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCAttentionAI::loadParams_() {
    getStaticParam(&mDurationTime_s, "DurationTime");
    getStaticParam(&mTurnAngleDiff_s, "TurnAngleDiff");
    getStaticParam(&mIsUseSight_s, "IsUseSight");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void NPCAttentionAI::m34() {
    changeChild("注目");
}

}  // namespace uking::ai
