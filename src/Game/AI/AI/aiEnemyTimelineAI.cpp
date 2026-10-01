#include "Game/AI/AI/aiEnemyTimelineAI.h"
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

}  // namespace uking::ai
