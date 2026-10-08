#include "Game/AI/AI/aiMoriblinSpearNearBattle.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

MoriblinSpearNearBattle::MoriblinSpearNearBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void MoriblinSpearNearBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    // NON_MATCHING: the original loads the target's x / z before the actor's translation (ours
    // interleaves them); the instructions are otherwise identical (same scheduling note as calc_).
    if (testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0) ||
        testRootAiFlag2(ksys::act::ai::RootAiFlag2::_4)) {
        const f32 dx = mTargetPos_d->x - mActor->getMtx().m[0][3];
        const f32 dz = mTargetPos_d->z - mActor->getMtx().m[2][3];
        const sead::Vector3f diff(dx, 0.0f, dz);
        if (diff.length() <= sub_71007320F0(mActor, *mWeaponIdx_s) + *mNearDist_s) {
            const sead::Vector3f target_pos = *mTargetPos_d;
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(target_pos, "TargetPos", -1);
            changeChild("後退", &pack);
            return;
        }
    }
    auto* random = sead::GlobalRandom::instance();
    const u32 r = random->getU32();
    const s32 per = s32((u64(r) * 100) >> 32);
    if (per < *mBackWalkPer_s) {
        const sead::Vector3f target_pos = *mTargetPos_d;
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(target_pos, "TargetPos", -1);
        changeChild("後退", &pack);
        return;
    }
    if (per < *mBackStepPer_s + *mBackWalkPer_s) {
        changeToBackStep();
        return;
    }
    const sead::Vector3f target_pos = *mTargetPos_d;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target_pos, "TargetPos", -1);
    changeChild("大攻撃", &pack);
}

// NON_MATCHING: the original loads the target's x / z before the actor's translation (ours the other way round)
// and orders the stack slots differently (the SafeString temporaries of the second isCurrentChild() below the
// InlineParamPack and the target copy above it); the instructions are otherwise identical
void MoriblinSpearNearBattle::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("バックステップ") || isCurrentChild("大攻撃")) {
            sead::Vector3f diff = *mTargetPos_d - mActor->getMtx().getTranslation();
            diff.y = 0;
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
