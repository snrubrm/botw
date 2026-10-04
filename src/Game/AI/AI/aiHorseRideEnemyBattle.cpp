#include "Game/AI/AI/aiHorseRideEnemyBattle.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

HorseRideEnemyBattle::HorseRideEnemyBattle(const InitArg& arg) : EnemyBattle(arg) {}

HorseRideEnemyBattle::~HorseRideEnemyBattle() = default;

bool HorseRideEnemyBattle::init_(sead::Heap* heap) {
    return EnemyBattle::init_(heap);
}

void HorseRideEnemyBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
}

// NON_MATCHING: only the child's vtable load: the original hoists `load vtable` above the branches that follow the
// isFinished() / isFailed() calls (one `ldr x8, [child]` shared by the isFailed() / isChangeable() arms); ours loads it
// in each arm (same family as EnemyMoveToGround / ForestGiantChanceWait)
void HorseRideEnemyBattle::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (child->isFailed()) {
            setFailed();
            return;
        }
        if (isCurrentChild("戦闘準備")) {
            if (m39()) {
                m38();
            } else {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
                changeChild("攻撃待機", &pack);
            }
            return;
        }
        if (isCurrentChild("攻撃待機")) {
            m38();
            return;
        }
        if (isCurrentChild("戦闘攻撃")) {
            sub_7100381ED4();
            m37();
            return;
        }
    } else if (child->isChangeable()) {
        if (isCurrentChild("戦闘準備")) {
            auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
            if (!enemy || enemy->_e68.value <= sead::Mathf::epsilon()) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
                changeChild("攻撃待機", &pack);
            }
        }
        if (!isCurrentChild("戦闘攻撃") && m39()) {
            m38();
            return;
        }
    }

    child->setDynamicParam(sub_71005D9330(mActor), "TargetPos");
}

void HorseRideEnemyBattle::leave_() {
    EnemyBattle::leave_();
}

void HorseRideEnemyBattle::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mAttackRadius_s, "AttackRadius");
}

bool HorseRideEnemyBattle::m40() {
    const f32 dist = (sub_71005D9330(mActor) - mActor->getMtx().getTranslation()).length();
    if (dist <= *mAttackRadius_s + sub_71007320F0(mActor, *mWeaponIdx_s))
        return EnemyBattle::m40();
    return false;
}

}  // namespace uking::ai
