#include "Game/AI/AI/aiEnemyTimelineAI.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

EnemyTimelineAI::EnemyTimelineAI(const InitArg& arg) : TimelineAI(arg) {}

EnemyTimelineAI::~EnemyTimelineAI() = default;

bool EnemyTimelineAI::init_(sead::Heap* heap) {
    return TimelineAI::init_(heap);
}

void EnemyTimelineAI::enter_(ksys::act::ai::InlineParamPack* params) {
    TimelineAI::enter_(params);
    auto* actor = mActor;
    actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000000);
    actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
}

bool EnemyTimelineAI::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool EnemyTimelineAI::isFinished() const {
    return getCurrentChild()->isFinished();
}

void EnemyTimelineAI::leave_() {
    TimelineAI::leave_();
    if (auto* awareness = mActor->getAwareness())
        awareness->sub_7100D7E9BC(0);
}

void EnemyTimelineAI::loadParams_() {
    TimelineAI::loadParams_();
    getDynamicParam(&mCentralPos_d, "CentralPos");
}

void EnemyTimelineAI::calc_() {
    TimelineAI::calc_();
    getCurrentChild()->setDynamicParam(*mCentralPos_d, "CentralPos");
    getCurrentChild()->setDynamicParam(*mCentralPos_d, "TargetPos");
}

void EnemyTimelineAI::m36(const sead::SafeString& name, ksys::act::ai::InlineParamPack* params) {
    params->addVec3(*mCentralPos_d, "CentralPos", -1);
    params->addVec3(*mCentralPos_d, "TargetPos", -1);
}

}  // namespace uking::ai
