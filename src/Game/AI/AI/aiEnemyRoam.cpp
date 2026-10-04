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

// NON_MATCHING: only the operand order of the three final fadds (the original adds `forward * 3` first, ours the translation first; load schedule and registers match)
void EnemyRoam::changeToRoamSearch() {
    ksys::act::ai::InlineParamPack pack;
    const sead::Matrix34f& mtx = mActor->getMtx();
    const sead::Vector3f trans = mtx.getTranslation();
    const sead::Vector3f pos = mtx.getBase(2) * 3.0f + trans;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("徘徊探索", &pack);
}

}  // namespace uking::ai
