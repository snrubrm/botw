#include "Game/AI/AI/aiLynelLineMoveAttack.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

LynelLineMoveAttack::LynelLineMoveAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelLineMoveAttack::~LynelLineMoveAttack() = default;

bool LynelLineMoveAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelLineMoveAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mIsSkipPrepare_d) {
        const f32 radius = *mGoalRadius_s;
        const f32 dist = radius + sub_71007320F0(mActor, *mWeaponIdx_s);
        if (sub_710072CB78(mActor, *mTargetPos_d, nullptr, dist, -1)) {
            changeToAttack();
            return;
        }
    }
    changeToPrepare();
}

void LynelLineMoveAttack::changeToAttack() {
    ksys::act::ai::InlineParamPack params;
    params.addVec3(*mTargetPos_d, "TargetPos", -1);
    params.addVec3(*mTargetVel_d, "TargetVel", -1);
    changeChild("攻撃", &params);
}

void LynelLineMoveAttack::changeToPrepare() {
    ksys::act::ai::InlineParamPack params;
    params.addVec3(*mTargetPos_d, "TargetPos", -1);
    params.addVec3(*mTargetVel_d, "TargetVel", -1);
    changeChild("準備", &params);
}

void LynelLineMoveAttack::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("準備") && child->isFinished()) {
            const f32 radius = *mGoalRadius_s;
            const f32 dist = radius + sub_71007320F0(mActor, *mWeaponIdx_s);
            if (!sub_710072CB78(mActor, *mTargetPos_d, nullptr, dist, -1)) {
                setFailed();
                return;
            }
            changeToAttack();
            return;
        }
    } else {
        child->isChangeable();
    }

    auto* current = getCurrentChild();
    current->setDynamicParam(*mTargetPos_d, "TargetPos");
    current->setDynamicParam(*mTargetVel_d, "TargetVel");
}

bool LynelLineMoveAttack::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

void LynelLineMoveAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelLineMoveAttack::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mGoalRadius_s, "GoalRadius");
    getDynamicParam(&mIsSkipPrepare_d, "IsSkipPrepare");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetVel_d, "TargetVel");
}

bool LynelLineMoveAttack::isFinished() const {
    return isCurrentChild("攻撃") && getCurrentChild()->isFinished();
}

}  // namespace uking::ai
