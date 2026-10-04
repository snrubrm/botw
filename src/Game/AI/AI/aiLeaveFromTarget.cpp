#include "Game/AI/AI/aiLeaveFromTarget.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

LeaveFromTarget::LeaveFromTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LeaveFromTarget::~LeaveFromTarget() = default;

void LeaveFromTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

// NON_MATCHING: same operations; the original keeps `goal` in the stack slot shared with the InlineParamPack (ours
// has a separate slot below it) and schedules the target / actor loads slightly differently
void LeaveFromTarget::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (mActor) {
            const sead::Vector3f pos = mActor->getMtx().getTranslation();
            const sead::Vector2f diff(pos.x - mTargetPos_d->x, pos.z - mTargetPos_d->z);
            if (diff.length() >= *mLeaveDist_s) {
                setFinished();
                return;
            }
            if (mActor) {
                sead::Vector3f actor_pos;
                mActor->getMtx().getTranslation(actor_pos);
                sead::Vector3f dir(actor_pos.x - mTargetPos_d->x, 0.0f, actor_pos.z - mTargetPos_d->z);
                dir.normalize();
                sead::Vector3f goal = actor_pos;
                goal += dir * *mLeaveDist_s;
                if (sub_710072FAB0(mActor, goal, nullptr, -1, -1.0f, -1.0f)) {
                    ksys::act::ai::InlineParamPack pack;
                    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
                    changeChild("後ずさり", &pack);
                    return;
                }
            }
        }

        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("逃走", &pack);
    } else {
        getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
    }
}

void LeaveFromTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LeaveFromTarget::loadParams_() {
    getStaticParam(&mLeaveDist_s, "LeaveDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
