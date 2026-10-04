#include "Game/AI/AI/aiMoriblinSpearNearBattle.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

MoriblinSpearNearBattle::MoriblinSpearNearBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void MoriblinSpearNearBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

// NON_MATCHING: only the order of the stack slots (the original puts the SafeString temporaries of the second
// isCurrentChild() / "TargetPos" below the InlineParamPack and the target copy above it; ours has them the other
// way round); everything else is identical
void MoriblinSpearNearBattle::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("バックステップ") || isCurrentChild("大攻撃")) {
            const f32 target_x = mTargetPos_d->x;
            const f32 target_z = mTargetPos_d->z;
            const f32 pos_x = mActor->getMtx()(0, 3);
            const f32 pos_z = mActor->getMtx()(2, 3);
            const sead::Vector3f diff(target_x - pos_x, 0.0f, target_z - pos_z);
            const f32 dist = diff.length();
            if (dist <= sub_71007320F0(mActor, *mWeaponIdx_s) + *mNearDist_s) {
                const sead::Vector3f target_pos = *mTargetPos_d;
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(target_pos, "TargetPos", -1);
                changeChild("後退", &pack);
            } else {
                setFinished();
            }
        } else if (isCurrentChild("後退")) {
            if (getCurrentChild()->isFinished())
                setFinished();
            else if (getCurrentChild()->isFailed())
                setFailed();
        }
    } else {
        getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
    }
}

// NON_MATCHING: the original keeps separate `return true` blocks feeding one exit, loads the
// translation before the target position and sets a dead per-case bool (w20)
bool MoriblinSpearNearBattle::isFinished() const {
    if (ksys::act::ai::ActionBase::isFinished())
        return true;
    if (isCurrentChild("後退")) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed())
            return true;
    }
    if (isCurrentChild("バックステップ") || isCurrentChild("大攻撃")) {
        sead::Vector3f diff = *mTargetPos_d - mActor->getMtx().getTranslation();
        diff.y = 0;
        const f32 dist = diff.length();
        if (dist <= sub_71007320F0(mActor, *mWeaponIdx_s) + *mNearDist_s)
            return false;
        return getCurrentChild()->isFinished();
    }
    return false;
}

bool MoriblinSpearNearBattle::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void MoriblinSpearNearBattle::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MoriblinSpearNearBattle::loadParams_() {
    getStaticParam(&mBackWalkPer_s, "BackWalkPer");
    getStaticParam(&mBackStepPer_s, "BackStepPer");
    getStaticParam(&mNearDist_s, "NearDist");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void MoriblinSpearNearBattle::changeToBackStep() {
    const sead::Vector3f target_pos = *mTargetPos_d;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target_pos, "TargetPos", -1);
    pack.addInt(100, "AttackPer", -1);
    changeChild("バックステップ", &pack);
}

}  // namespace uking::ai
