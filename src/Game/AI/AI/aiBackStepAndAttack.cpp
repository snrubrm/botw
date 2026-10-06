#include "Game/AI/AI/aiBackStepAndAttack.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::ai {

BackStepAndAttack::BackStepAndAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BackStepAndAttack::~BackStepAndAttack() = default;

bool BackStepAndAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// 0x7100327300: whether the target lies within the cone of the given angle in front of the actor
// (both directions projected on the plane perpendicular to the actor's up direction).
bool sub_7100327300(const sead::Vector3f& target, ksys::act::Actor* actor, f32 angle) {
    sead::Vector3f to_target = target - actor->getMtx().getTranslation();
    ksys::util::sub_71011EFA00(&to_target, to_target, getUpDir(actor));
    to_target.normalize();
    sead::Vector3f front;
    sub_71000891C8(&front, actor);
    return front.dot(to_target) >= sead::Mathf::cos(angle);
}

bool BackStepAndAttack::sub_7100326B38(sead::Vector3f* out_pos) {
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    sead::Vector3f direction = pos - *mTargetPos_d;
    direction.normalize();
    sead::Vector3f ray;
    sead::Vector3f hit;
    for (const f32 angle : {0.0f, -sead::Mathf::pi() / 4, sead::Mathf::pi() / 4}) {
        ray = direction;
        ksys::util::sub_71011EF010(&ray, angle);
        if (sub_710072FD28(mActor, ray, &hit, -1, *mBackStepDist_s, -1.0f, -1.0f, -1.0f)) {
            *out_pos = hit;
            return true;
        }
        const f32 dx = pos.x - hit.x;
        const f32 dz = pos.z - hit.z;
        if (dx * dx + dz * dz >= *mBackStepMinDist_s * *mBackStepMinDist_s) {
            *out_pos = hit;
            return true;
        }
    }
    return false;
}

void BackStepAndAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    _70 = 0;
    _74 = 0;
    const sead::Vector3f delta = mActor->getMtx().getTranslation() - *mTargetPos_d;
    if (!(delta.x * delta.x + delta.z * delta.z >= *mNoBackStepRange_s * *mNoBackStepRange_s)) {
        sead::Vector3f target;
        if (sub_7100326B38(&target)) {
            ++_70;
            _74 = 0;
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(target, "TargetPos", -1);
            changeChild("バックステップ", &pack);
            return;
        }
    }
    if (sub_7100327300(*mTargetPos_d, mActor, *mFrontAngle_s)) {
        _74 = 0;
        changeChildWithTargetPos("攻撃");
    } else {
        ++_74;
        changeChildWithTargetPos("回転");
    }
}

// NON_MATCHING: the original hoists the child vtable load above the isFinished()/isFailed() branches.
void BackStepAndAttack::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (child->isFailed()) {
            setFailed();
            return;
        }
        if (isCurrentChild("攻撃")) {
            setFinished();
            return;
        }
    } else {
        child->isChangeable();
        if (!isCurrentChild("バックステップ"))
            getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
        return;
    }
    const int back_step_max = *mBackStepMax_s;
    if (back_step_max < 0 || _70 < back_step_max) {
        const sead::Vector3f delta = mActor->getMtx().getTranslation() - *mTargetPos_d;
        if (!(delta.x * delta.x + delta.z * delta.z >=
              *mNoBackStepRange_s * *mNoBackStepRange_s)) {
            sead::Vector3f target;
            if (sub_7100326B38(&target)) {
                ++_70;
                _74 = 0;
                ksys::act::ai::InlineParamPack pack;
            pack.addVec3(target, "TargetPos", -1);
            changeChild("バックステップ", &pack);
                return;
            }
        }
    }
    const int turn_repeat_max = *mTurnRepeatMax_s;
    if ((turn_repeat_max >= 0 && _74 >= turn_repeat_max) ||
        sub_7100327300(*mTargetPos_d, mActor, *mFrontAngle_s)) {
        _74 = 0;
        changeChildWithTargetPos("攻撃");
    } else {
        ++_74;
        changeChildWithTargetPos("回転");
    }
}

bool BackStepAndAttack::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

void BackStepAndAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void BackStepAndAttack::loadParams_() {
    getStaticParam(&mBackStepMax_s, "BackStepMax");
    getStaticParam(&mTurnRepeatMax_s, "TurnRepeatMax");
    getStaticParam(&mBackStepMinDist_s, "BackStepMinDist");
    getStaticParam(&mBackStepDist_s, "BackStepDist");
    getStaticParam(&mFrontAngle_s, "FrontAngle");
    getStaticParam(&mNoBackStepRange_s, "NoBackStepRange");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool BackStepAndAttack::isFinished() const {
    return ActionBase::isFinished() || (isCurrentChild("攻撃") && getCurrentChild()->isFinished());
}

}  // namespace uking::ai
