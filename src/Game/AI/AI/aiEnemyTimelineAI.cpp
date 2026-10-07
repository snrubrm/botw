#include "Game/AI/AI/aiEnemyTimelineAI.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/World/worldManager.h"

namespace uking::ai {

bool EnemyTimelineAI::m35(const sead::SafeString& name) {
    if (name != "Sleep")
        return true;
    if (auto* manager = ksys::world::Manager::instance(); manager && manager->isAocField())
        return false;
    if (auto* placement = ksys::map::PlacementMgr::instance();
        placement && placement->mTeraSystem) {
        bool below = false;
        f32 height = 0.0f;
        ksys::map::sub_7100EDB6E0(&below, &height, placement->mTeraSystem, mCentralPos_d);
        return !below;
    }
    return true;
}



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

const sead::SafeString& EnemyTimelineAI::m34() {
    const auto& name = TimelineAI::m34();
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (enemy && enemy->_e84.isOnBit(24) && name == "Sleep") {
        static const sead::SafeString sUnk_71025b8d98 = "Idle";
        return sUnk_71025b8d98;
    }
    return name;
}

void EnemyTimelineAI::m36(const sead::SafeString& name, ksys::act::ai::InlineParamPack* params) {
    params->addVec3(*mCentralPos_d, "CentralPos", -1);
    params->addVec3(*mCentralPos_d, "TargetPos", -1);
}

}  // namespace uking::ai
