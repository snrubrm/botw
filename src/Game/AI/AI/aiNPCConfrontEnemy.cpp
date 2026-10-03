#include "Game/AI/AI/aiNPCConfrontEnemy.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

// NON_MATCHING: the original issues the 60 zero stores of `_98` (descending: 0xd0, 0x98, 0xc0, 0xb0, 0xa0) after the
// memset of the parameters; ours hoists them above it (same instructions otherwise)
NPCConfrontEnemy::NPCConfrontEnemy(const InitArg& arg) : ksys::act::ai::Ai(arg), _98(), _e8() {}

// NON_MATCHING: the original computes `this + 0x188` (CriticalSection) before the first BaseProcLink reset and keeps
// it in x21 (as in NPCRunaway's destructor)
NPCConfrontEnemy::~NPCConfrontEnemy() = default;

bool NPCConfrontEnemy::init_(sead::Heap* heap) {
    _88 = sead::DynamicCast<act::NPC>(mActor);
    return true;
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
