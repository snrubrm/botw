#include "Game/AI/AI/aiNPCRunaway.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectNpc.h"

namespace uking::ai {

// NON_MATCHING: the original computes `this + 0xd8` into x20 before the memset of `_90` (ours right before the
// BaseProcLink call); same address-hoisting as `this + 0x188` in the destructor
NPCRunaway::NPCRunaway(const InitArg& arg) : ksys::act::ai::Ai(arg), _90(), _e8() {}

NPCRunaway::~NPCRunaway() = default;

bool NPCRunaway::init_(sead::Heap* heap) {
    _80 = sead::DynamicCast<act::NPC>(mActor);
    _88 = mActor->getParam()->getRes().mGParamList->getNpc()->mTolerantTime.ref();
    return true;
}

void NPCRunaway::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCRunaway::leave_() {
    mActor->getLodState()->mFlags8.reset(0x40000);
    sub_71005D7518(mActor, true);
}

void NPCRunaway::loadParams_() {
    getStaticParam(&mReleaseDistance_s, "ReleaseDistance");
    getStaticParam(&mCorneredDistance_s, "CorneredDistance");
    getStaticParam(&mStandRateTime_s, "StandRateTime");
    getStaticParam(&mStandingTime_s, "StandingTime");
    getDynamicParam(&mTerrorLevel_d, "TerrorLevel");
    getDynamicParam(&mTerrorLayer_d, "TerrorLayer");
    getDynamicParam(&mIsReturnFromDemo_d, "IsReturnFromDemo");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetVel_d, "TargetVel");
}

}  // namespace uking::ai
