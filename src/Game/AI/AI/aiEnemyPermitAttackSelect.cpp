#include "Game/AI/AI/aiEnemyPermitAttackSelect.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actEnemy.h"
#include "Game/Damage/dmgInfoManager.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

EnemyPermitAttackSelect::EnemyPermitAttackSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyPermitAttackSelect::~EnemyPermitAttackSelect() = default;

bool EnemyPermitAttackSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyPermitAttackSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (sead::IsDerivedFrom<act::Enemy>(actor)) {
        const f32 timer = static_cast<act::Enemy*>(actor)->_e68.value;
        if (*mIsIgnoreEnemyMgr_s || !(timer <= sead::Mathf::epsilon())) {
            if (!*mIsIgnoreEnemyMgr_s)
                changeChild("攻撃禁止", params);
            else if (timer <= sead::Mathf::epsilon())
                changeChild("攻撃許可", params);
            else
                changeChild("攻撃禁止", params);
            return;
        }
    }

    if (dmg::DamageInfoMgr::instance()->get4f8().sub_7100671A64(mActor))
        changeChild("攻撃許可", params);
    else
        changeChild("攻撃禁止", params);
}

void EnemyPermitAttackSelect::calc_() {
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed() && child->isChangeable()) {
        auto* actor = mActor;
        if (sead::IsDerivedFrom<act::Enemy>(actor)) {
            const f32 timer = static_cast<act::Enemy*>(actor)->_e68.value;
            if (*mIsIgnoreEnemyMgr_s || !(timer <= sead::Mathf::epsilon())) {
                if (*mIsIgnoreEnemyMgr_s && timer <= sead::Mathf::epsilon()) {
                    if (!isCurrentChild("攻撃許可"))
                        changeChild("攻撃許可");
                } else if (!isCurrentChild("攻撃禁止")) {
                    changeChild("攻撃禁止");
                }
                return;
            }
        }

        if (dmg::DamageInfoMgr::instance()->get4f8().sub_7100671A64(mActor)) {
            if (!isCurrentChild("攻撃許可"))
                changeChild("攻撃許可");
        } else if (!isCurrentChild("攻撃禁止")) {
            changeChild("攻撃禁止");
        }
    }
}

bool EnemyPermitAttackSelect::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool EnemyPermitAttackSelect::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

void EnemyPermitAttackSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyPermitAttackSelect::loadParams_() {
    getStaticParam(&mIsIgnoreEnemyMgr_s, "IsIgnoreEnemyMgr");
}

}  // namespace uking::ai
