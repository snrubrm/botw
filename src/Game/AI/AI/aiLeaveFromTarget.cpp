#include "Game/AI/AI/aiLeaveFromTarget.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

LeaveFromTarget::LeaveFromTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LeaveFromTarget::~LeaveFromTarget() = default;

// NON_MATCHING: Position loads, goal stores and floating-point register allocation differ.
void LeaveFromTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    bool can_step_back = false;
    if (mActor) {
        const sead::Vector3f position = mActor->getMtx().getTranslation();
        sead::Vector3f direction(position.x - mTargetPos_d->x, 0.0f,
                                 position.z - mTargetPos_d->z);
        direction.normalize();
        const sead::Vector3f goal = position + direction * *mLeaveDist_s;
        can_step_back = sub_710072FAB0(mActor, goal, nullptr, -1, -1.0f, -1.0f);
    }
    if (can_step_back) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("後ずさり", &pack);
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("逃走", &pack);
    }
}

// NON_MATCHING: only the register numbering / load schedule of the direction (the original loads the actor's x / z as
// integers first, the y after the sqrt, and numbers x / z s11 / s10); stack slots match (the `goal` / pack share a slot
// because the step-back test is evaluated in its own scope before the pack is built)
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
            bool can_step_back = false;
            if (mActor) {
                sead::Vector3f actor_pos;
                mActor->getMtx().getTranslation(actor_pos);
                sead::Vector3f dir = actor_pos;
                dir -= *mTargetPos_d;
                dir.y = 0.0f;
                dir.normalize();
                sead::Vector3f goal = actor_pos;
                goal += dir * *mLeaveDist_s;
                can_step_back = sub_710072FAB0(mActor, goal, nullptr, -1, -1.0f, -1.0f);
            }
            if (can_step_back) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(*mTargetPos_d, "TargetPos", -1);
                changeChild("後ずさり", &pack);
                return;
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
