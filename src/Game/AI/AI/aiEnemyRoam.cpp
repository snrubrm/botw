#include "Game/AI/AI/aiEnemyRoam.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

EnemyRoam::EnemyRoam(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void EnemyRoam::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000000);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    _60 = false;
    changeChild("徘徊待機");
}

void EnemyRoam::loadParams_() {
    getStaticParam(&mSearchPer_s, "SearchPer");
    getStaticParam(&mTerritoryRadius_s, "TerritoryRadius");
    getStaticParam(&mTerritoryRadiusRnd_s, "TerritoryRadiusRnd");
    getStaticParam(&mMinMoveDist_s, "MinMoveDist");
    getDynamicParam(&mCentralPos_d, "CentralPos");
}

}  // namespace uking::ai
