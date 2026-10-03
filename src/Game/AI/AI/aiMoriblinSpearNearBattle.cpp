#include "Game/AI/AI/aiMoriblinSpearNearBattle.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

MoriblinSpearNearBattle::MoriblinSpearNearBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void MoriblinSpearNearBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
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

void MoriblinSpearNearBattle::sub_71004ABC20() {
    const sead::Vector3f target_pos = *mTargetPos_d;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target_pos, "TargetPos", -1);
    pack.addInt(100, "AttackPer", -1);
    changeChild("バックステップ", &pack);
}

}  // namespace uking::ai
