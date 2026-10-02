#include "Game/AI/AI/aiNPCConfrontEnemy.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

NPCConfrontEnemy::NPCConfrontEnemy(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCConfrontEnemy::~NPCConfrontEnemy() = default;

bool NPCConfrontEnemy::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NPCConfrontEnemy::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCConfrontEnemy::leave_() {
    mActor->getLodState()->mFlags8.reset(0x40000);
    sub_71005D7518(mActor, true);
}

void NPCConfrontEnemy::loadParams_() {
    getStaticParam(&mReleaseDistance_s, "ReleaseDistance");
    getStaticParam(&mReleaseTime_s, "ReleaseTime");
    getStaticParam(&mRewardDistance_s, "RewardDistance");
    getStaticParam(&mTerrorDistAfterPlayerRescue_s, "TerrorDistAfterPlayerRescue");
    getDynamicParam(&mTerrorLevel_d, "TerrorLevel");
    getDynamicParam(&mTerrorLayer_d, "TerrorLayer");
    getDynamicParam(&mIsReturnFromDemo_d, "IsReturnFromDemo");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetVel_d, "TargetVel");
    getMapUnitParam(&mTerritoryArea_m, "TerritoryArea");
}

}  // namespace uking::ai
