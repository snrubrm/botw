#include "Game/AI/AI/aiLeaderDistanceSelector.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

LeaderDistanceSelector::LeaderDistanceSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LeaderDistanceSelector::~LeaderDistanceSelector() = default;

bool LeaderDistanceSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LeaderDistanceSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710047F77C();
}

void LeaderDistanceSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LeaderDistanceSelector::loadParams_() {
    getStaticParam(&mBoundaryDistance_s, "BoundaryDistance");
    getStaticParam(&mOverlapDistance_s, "OverlapDistance");
    getDynamicParam(&mLeaderActor_d, "LeaderActor");
}

void LeaderDistanceSelector::sub_710047F77C() {
    ksys::act::ActorConstDataAccess acc;
    ksys::act::acquireActor(mLeaderActor_d, &acc);
    sead::Vector3f pos;
    acc.getActorMtx().getTranslation(pos);

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    pack.addFloat(*mBoundaryDistance_s, "KeepTargetRange", -1);
    changeChild("内側", &pack);
}

}  // namespace uking::ai
