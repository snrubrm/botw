#include "Game/AI/AI/aiLeadToTarget.h"
#include <math/seadMathCalcCommon.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

LeadToTarget::LeadToTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LeadToTarget::~LeadToTarget() = default;

bool LeadToTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LeadToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    _94 = false;
    _78.value = 0;
    _78.previous_value = 0;
    sub_710047FE18();
}

// NON_MATCHING: stack layout of the SafeString / accessor temporaries and the float load scheduling of the
// distance tests; the control flow, calls and compares match.
void LeadToTarget::calc_() {
    if (isCurrentChild("待機")) {
        if (auto* nav = mActor->m45()) {
            u8 nav_state;
            {
                auto lock = sead::makeScopedLock(nav->_1e0);
                nav_state = nav->_294;
            }
            if (nav_state == 3) {
                const f32 ax = mActor->getMtx().m[0][3];
                const f32 az = mActor->getMtx().m[2][3];
                const f32 dx = ax - mTargetPos_d->x;
                const f32 dz = az - mTargetPos_d->z;
                if (dx * dx + dz * dz > _90) {
                    setFailed();
                    return;
                }
            }
        }
        if (_94) {
            _78.update();
            if (_78.value <= sead::Mathf::epsilon())
                setFinished();
            return;
        }
        if (!isFinished() && !isFailed()) {
            bool ahead_check = true;
            {
                ksys::act::ActorConstDataAccess accessor;
                if (ksys::act::acquireActor(mLeaderActor_d, &accessor)) {
                    const auto& leader_mtx = accessor.getActorMtx();
                    const f32 lx = leader_mtx.m[0][3];
                    const f32 lz = leader_mtx.m[2][3];
                    const f32 limit = _8c;
                    const f32 dx = mActor->getMtx().m[0][3] - lx;
                    const f32 dz = mActor->getMtx().m[2][3] - lz;
                    const f32 dist = dx * dx + dz * dz;
                    if (dist <= limit) {
                        sub_710047FE18();
                        ahead_check = false;
                    }
                }
            }
            if (ahead_check && *mDontWaitIfLeaderIsAhead_s) {
                ksys::act::ActorConstDataAccess accessor;
                if (ksys::act::acquireActor(mLeaderActor_d, &accessor)) {
                    const auto& leader_mtx = accessor.getActorMtx();
                    const f32 ax = mActor->getMtx().m[0][3];
                    const f32 az = mActor->getMtx().m[2][3];
                    const f32 lx = leader_mtx.m[0][3];
                    const f32 lz = leader_mtx.m[2][3];
                    const f32 tx = mTargetPos_d->x;
                    const f32 tz = mTargetPos_d->z;
                    const f32 dx = tx - lx;
                    const f32 dz = tz - lz;
                    const f32 leader_dist = dx * dx + dz * dz;
                    const f32 ex = tx - ax;
                    const f32 ez = tz - az;
                    const f32 actor_dist = ex * ex + ez * ez - 625.0f;
                    if (leader_dist < actor_dist)
                        sub_710047FE18();
                }
            }
        }
    } else if (isCurrentChild("誘導") || isCurrentChild("誘導(騎乗)")) {
        bool near_leader = true;
        {
            ksys::act::ActorConstDataAccess accessor;
            if (ksys::act::acquireActor(mLeaderActor_d, &accessor)) {
                const auto& leader_mtx = accessor.getActorMtx();
                const f32 lx = leader_mtx.m[0][3];
                const f32 lz = leader_mtx.m[2][3];
                const f32 limit = _88;
                const f32 dx = mActor->getMtx().m[0][3] - lx;
                const f32 dz = mActor->getMtx().m[2][3] - lz;
                near_leader = !(dx * dx + dz * dz >= limit);
            }
        }
        if (near_leader) {
            const f32 ax = mActor->getMtx().m[0][3];
            const f32 az = mActor->getMtx().m[2][3];
            const f32 dx = ax - mTargetPos_d->x;
            const f32 dz = az - mTargetPos_d->z;
            if (!(dx * dx + dz * dz > _84)) {
                _78.value = _78.previous_value = *mWaitFramesAfterArrive_s;
                _94 = true;
                changeToWait();
            }
        } else if (!*mDontWaitIfLeaderIsAhead_s) {
            changeToWait();
        } else {
            ksys::act::ActorConstDataAccess accessor;
            if (ksys::act::acquireActor(mLeaderActor_d, &accessor)) {
                const auto& leader_mtx = accessor.getActorMtx();
                const f32 ax = mActor->getMtx().m[0][3];
                const f32 az = mActor->getMtx().m[2][3];
                const f32 lx = leader_mtx.m[0][3];
                const f32 lz = leader_mtx.m[2][3];
                const f32 tx = mTargetPos_d->x;
                const f32 tz = mTargetPos_d->z;
                const f32 dx = tx - lx;
                const f32 dz = tz - lz;
                const f32 leader_dist = dx * dx + dz * dz;
                const f32 ex = tx - ax;
                const f32 ez = tz - az;
                const f32 actor_dist = ex * ex + ez * ez + 1250.0f;
                if (!(leader_dist < actor_dist))
                    changeToWait();
            } else {
                changeToWait();
            }
        }
    }

    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return;
    if (!isCurrentChild("誘導") && !isCurrentChild("誘導(騎乗)"))
        return;
    if (isFinished() || isFailed())
        return;
    if (!child->isFinished()) {
        if (!child->isFailed()) {
            changeToWait();
            return;
        }
        const f32 ax = mActor->getMtx().m[0][3];
        const f32 az = mActor->getMtx().m[2][3];
        const f32 dx = ax - mTargetPos_d->x;
        const f32 dz = az - mTargetPos_d->z;
        if (dx * dx + dz * dz > _90) {
            setFailed();
            changeToWait();
            return;
        }
    }
    _78.value = _78.previous_value = *mWaitFramesAfterArrive_s;
    _94 = true;
    changeToWait();
}

void LeadToTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LeadToTarget::loadParams_() {
    if (getStaticParam(&mSuccessRadius_s, "SuccessRadius"))
        _84 = *mSuccessRadius_s * *mSuccessRadius_s;
    if (getStaticParam(&mWaitDistance_s, "WaitDistance"))
        _88 = *mWaitDistance_s * *mWaitDistance_s;
    if (getStaticParam(&mResumeLeadDistance_s, "ResumeLeadDistance"))
        _8c = *mResumeLeadDistance_s * *mResumeLeadDistance_s;
    if (getStaticParam(&mOkPathFailRange_s, "OkPathFailRange"))
        _90 = *mOkPathFailRange_s * *mOkPathFailRange_s;
    getStaticParam(&mDontWaitIfLeaderIsAhead_s, "DontWaitIfLeaderIsAhead");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mLeaderActor_d, "LeaderActor");
    getStaticParam(&mWaitFramesAfterArrive_s, "WaitFramesAfterArrive");
}

void LeadToTarget::sub_710047FE18() {
    ksys::act::ai::InlineParamPack params;
    params.addVec3(*mTargetPos_d, "TargetPos", -1);
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(mLeaderActor_d, &accessor)) {
        if (accessor.sub_7100D12E64())
            changeChild("誘導(騎乗)", &params);
        else
            changeChild("誘導", &params);
    }
}

void LeadToTarget::changeToWait() {
    if (!isCurrentChild("待機")) {
        ksys::act::ai::InlineParamPack pack;
        pack.addActor(*mLeaderActor_d, "LeaderActor", -1);
        changeChild("待機", &pack);
    }
}

}  // namespace uking::ai
