#include "Game/AI/AI/aiWaitAndFaceLeader.h"
#include <cmath>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::ai {

WaitAndFaceLeader::WaitAndFaceLeader(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WaitAndFaceLeader::~WaitAndFaceLeader() = default;

bool WaitAndFaceLeader::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING (M): the math is the same but the original keeps the leader position as raw 32-bit words
// and schedules the two xz terms and the cross product differently; same body as calc_'s turn check
void WaitAndFaceLeader::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ActorConstDataAccess accessor;
    if (!ksys::act::acquireActor(mLeaderActor_d, &accessor)) {
        setFailed();
        return;
    }

    sead::Vector3f leader_pos;
    accessor.getActorMtx().getTranslation(leader_pos);
    const f32 dist_sq = ksys::util::sqXZDistance(mActor->getMtx().getTranslation(), leader_pos);
    sead::Vector3f dir = leader_pos - mActor->getMtx().getTranslation();
    dir.y = 0;
    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    sead::Vector3f cross;
    cross.setCross(front, dir);
    const f32 angle = std::atan2(cross.length(), front.dot(dir));

    if (dist_sq >= 9.0f && angle >= *mTurnThreshold_s) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(leader_pos + accessor.getVelocity() * 15.0f, "TargetPos", -1);
        changeChild("リーダーを向く", &pack);
    } else {
        changeChild("待機");
    }
}

// NON_MATCHING (M): see enter_
void WaitAndFaceLeader::calc_() {
    if (isFailed())
        return;

    if (isCurrentChild("待機")) {
        ksys::act::ActorConstDataAccess accessor;
        if (!ksys::act::acquireActor(mLeaderActor_d, &accessor)) {
            setFailed();
            return;
        }

        sead::Vector3f leader_pos;
        accessor.getActorMtx().getTranslation(leader_pos);
        const f32 dist_sq =
            ksys::util::sqXZDistance(mActor->getMtx().getTranslation(), leader_pos);
        sead::Vector3f dir = leader_pos - mActor->getMtx().getTranslation();
        dir.y = 0;
        sead::Vector3f front;
        mActor->getMtx().getBase(front, 2);
        sead::Vector3f cross;
        cross.setCross(front, dir);
        const f32 angle = std::atan2(cross.length(), front.dot(dir));

        if (dist_sq >= 9.0f && angle >= *mTurnThreshold_s) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(leader_pos + accessor.getVelocity() * 15.0f, "TargetPos", -1);
            changeChild("リーダーを向く", &pack);
        }
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed())
        changeChild("待機");
}

void WaitAndFaceLeader::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WaitAndFaceLeader::loadParams_() {
    getStaticParam(&mTurnThreshold_s, "TurnThreshold");
    getDynamicParam(&mLeaderActor_d, "LeaderActor");
}

}  // namespace uking::ai
