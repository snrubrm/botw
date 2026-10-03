#include "Game/AI/AI/aiForestGiantChanceWait.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::ai {

ForestGiantChanceWait::ForestGiantChanceWait(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ForestGiantChanceWait::~ForestGiantChanceWait() = default;

bool ForestGiantChanceWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

bool ForestGiantChanceWait::isTargetInFront() const {
    sead::Vector3f forward;
    sub_71000891C8(&forward, mActor);
    sead::Vector3f to_target = *mTargetPos_d - mActor->getMtx().getTranslation();
    to_target.y = 0;
    to_target.normalize();
    const f32 angle = *mTurnStartAngle_s;
    return to_target.dot(forward) >= sead::Mathf::cos(angle);
}

void ForestGiantChanceWait::enter_(ksys::act::ai::InlineParamPack* params) {
    _5c = false;
    const bool flag = testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0) ||
                      testRootAiFlag2(ksys::act::ai::RootAiFlag2::_4) ||
                      testRootAiFlag2(ksys::act::ai::RootAiFlag2::_1);
    if (!isTargetInFront()) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("回転", &pack);
    } else if (flag) {
        changeToWait(true);
    } else {
        changeToChance();
    }
}

void ForestGiantChanceWait::changeToChance() {
    if (_5c) {
        changeToWait(true);
        return;
    }
    _5c = true;
    const s32 roll = sead::GlobalRandom::instance()->getU32(100);
    if (roll > *mChanceRate_s + _58 * *mCorrectRate_s) {
        changeToWait(false);
        return;
    }
    _58 = _58 <= 0 ? _58 - 1 : 0;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e68.rate = 0;
    changeChild("チャンス");
}

void ForestGiantChanceWait::changeToWait(bool a2) {
    if (!a2)
        _58 = _58 >= 0 ? _58 + 1 : 0;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e68.rate = -1.0f;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("待機", &pack);
}

// NON_MATCHING: the original hoists the `[child]` vtable load above the branch of every child state
// test (shared tail for the two isFailed calls); ours reloads it in each branch
void ForestGiantChanceWait::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (child->isFailed()) {
            setFailed();
            return;
        }
        if (isCurrentChild("チャンス"))
            changeToWait(true);
        else if (isCurrentChild("回転"))
            changeToChance();
        else
            setFinished();
        return;
    }

    if (child->isChangeable()) {
        if (isCurrentChild("チャンス")) {
            if (!isTargetInFront()) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(*mTargetPos_d, "TargetPos", -1);
                changeChild("回転", &pack);
                return;
            }
        } else if (isCurrentChild("待機")) {
            if (!isTargetInFront()) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(*mTargetPos_d, "TargetPos", -1);
                changeChild("回転", &pack);
                return;
            }
        }
    }
    getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
}

void ForestGiantChanceWait::leave_() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e68.rate = -1.0f;
}

void ForestGiantChanceWait::loadParams_() {
    getStaticParam(&mChanceRate_s, "ChanceRate");
    getStaticParam(&mCorrectRate_s, "CorrectRate");
    getStaticParam(&mTurnStartAngle_s, "TurnStartAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool ForestGiantChanceWait::isChangeable() const {
    if (ksys::act::ai::Ai::isChangeable())
        return true;
    auto* child = getCurrentChild();
    if (child->isFinished())
        return true;
    return child->isFailed();
}

}  // namespace uking::ai
