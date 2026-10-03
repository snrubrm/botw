#include "Game/AI/AI/aiEnemyRoam.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
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

// NON_MATCHING: load scheduling of translation + forward * 3 (the original loads the three forward components first); same instructions otherwise
void EnemyRoam::sub_71003B2B00() {
    ksys::act::ai::InlineParamPack pack;
    const sead::Matrix34f& mtx = mActor->getMtx();
    const sead::Vector3f dir = mtx.getBase(2);
    sead::Vector3f pos(mtx(0, 3) + dir.x * 3.0f, mtx(1, 3) + dir.y * 3.0f, mtx(2, 3) + dir.z * 3.0f);
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("徘徊探索", &pack);
}

}  // namespace uking::ai
