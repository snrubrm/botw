#include "Game/AI/AI/aiLeaderDistanceSelector.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

LeaderDistanceSelector::LeaderDistanceSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LeaderDistanceSelector::~LeaderDistanceSelector() = default;

bool LeaderDistanceSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LeaderDistanceSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    changeToInside();
}

void LeaderDistanceSelector::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (child->isFinished())
            setFinished();
        else
            setFailed();
        return;
    }

    sead::Vector3f leader_pos;
    sead::Vector3f pos;
    {
        ksys::act::ActorConstDataAccess acc;
        ksys::act::acquireActor(mLeaderActor_d, &acc);
        const sead::Matrix34f& leader_mtx = acc.getActorMtx();
        leader_pos.set(leader_mtx.m[0][3], leader_mtx.m[1][3], leader_mtx.m[2][3]);
        pos.set(mActor->getMtx().m[0][3], mActor->getMtx().m[1][3], mActor->getMtx().m[2][3]);
    }

    if (child->isChangeable()) {
        const sead::Vector3f diff = pos - leader_pos;
        if (diff.squaredLength() >= _50 && !isCurrentChild("外側"))
            changeToOutside();
    }
}

void LeaderDistanceSelector::changeToOutside() {
    ksys::act::ActorConstDataAccess acc;
    ksys::act::acquireActor(mLeaderActor_d, &acc);
    sead::Vector3f pos;
    acc.getActorMtx().getTranslation(pos);

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("外側", &pack);
}

void LeaderDistanceSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LeaderDistanceSelector::loadParams_() {
    getStaticParam(&mBoundaryDistance_s, "BoundaryDistance");
    getStaticParam(&mOverlapDistance_s, "OverlapDistance");
    getDynamicParam(&mLeaderActor_d, "LeaderActor");
}

void LeaderDistanceSelector::changeToInside() {
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
