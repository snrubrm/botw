#include "Game/AI/AI/aiEnemyFeintBattle.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemyFeintBattle::EnemyFeintBattle(const InitArg& arg) : EnemyBattle(arg) {}

EnemyFeintBattle::~EnemyFeintBattle() = default;

void EnemyFeintBattle::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mIsAttackEnd_s, "IsAttackEnd");
}

void EnemyFeintBattle::calc_() {
    auto* child = getCurrentChild();
    bool is_prepare = false;
    if (child->isFinished() || child->isFailed())
        is_prepare = isCurrentChild("戦闘準備");

    child = getCurrentChild();
    if (is_prepare) {
        if (child->isFailed()) {
            setFailed();
            return;
        }
        ksys::act::ai::InlineParamPack params;
        params.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("フェイント", &params);
        return;
    }

    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("フェイント")) {
            m38();
            return;
        }
    }

    child = getCurrentChild();
    bool is_attack_end = false;
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("戦闘攻撃"))
            is_attack_end = *mIsAttackEnd_s;
    }

    child = getCurrentChild();
    if (is_attack_end) {
        if (child->isFinished())
            setFinished();
        else
            setFailed();
        return;
    }

    if (child->isChangeable() && isCurrentChild("戦闘準備")) {
        if (!sead::DynamicCast<act::Enemy>(mActor))
            return;
        if (!m39())
            return;
        ksys::act::ai::InlineParamPack params;
        params.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("フェイント", &params);
        return;
    }
    EnemyBattle::calc_();
}

bool EnemyFeintBattle::isFinished() const {
    if (*mIsAttackEnd_s && getCurrentChild()->isFinished() && isCurrentChild("戦闘攻撃"))
        return true;
    return ActionBase::isFinished();
}

bool EnemyFeintBattle::isFailed() const {
    if (*mIsAttackEnd_s && getCurrentChild()->isFailed() && isCurrentChild("戦闘攻撃"))
        return true;
    return ActionBase::isFailed();
}

}  // namespace uking::ai
