#include "Game/AI/AI/aiEnemyShieldSearchOrBattle.h"
#include "Game/Actor/actEnemy.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_710073033C.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

void EnemyShieldSearchOrBattle::changeToPickUpShield() {
    ksys::act::ai::InlineParamPack pack;
    pack.acquireActor(sead::DynamicCast<act::Weapon>(_70.getProc(nullptr, nullptr)), "TargetWeapon", -1);
    changeChild("盾拾い", &pack);
}

bool EnemyShieldSearchOrBattle::sub_71003BBD1C(ksys::act::BaseProcLink* out) {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (enemy && !enemy->sub_7100016284(*mParams.mShieldIdx_s) &&
        !enemy->sub_71000161A4(*mParams.mShieldIdx_s)) {
        auto* weapon = sead::DynamicCast<act::Weapon>(
            enemy->_c38[*mParams.mShieldIdx_s].getProc(nullptr, nullptr));
        if (sead::IsDerivedFrom<act::Weapon>(weapon) && !weapon->sub_71002E9A50()) {
            if (out)
                *out = enemy->_c38[*mParams.mShieldIdx_s];
            return true;
        }
    }
    return false;
}

EnemyShieldSearchOrBattle::EnemyShieldSearchOrBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyShieldSearchOrBattle::~EnemyShieldSearchOrBattle() = default;

bool EnemyShieldSearchOrBattle::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyShieldSearchOrBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyShieldSearchOrBattle::leave_() {
    ksys::act::ai::Ai::leave_();
}

// NON_MATCHING: shared normal-child transition merges the native parameter-pack lifetimes.
void EnemyShieldSearchOrBattle::calc_() {
    auto* child = getCurrentChild();
    bool normal = false;
    bool pick_up_shield = false;
    if (child->isFinished() || child->isFailed()) {
        const bool picking_up = isCurrentChild("盾拾い");
        const bool finished = child->isFinished();
        if (picking_up) {
            if (finished) {
                normal = true;
            } else {
                auto* actor = mActor;
                auto* target = sub_71005D9050(actor);
                if ((!target || !target->hasProc() ||
                     !sub_710073033C(actor, target, *mParams.mNoShieldSearchDist_s)) &&
                    sub_71003BC058(true))
                    pick_up_shield = true;
                else
                    normal = true;
            }
        } else {
            if (finished)
                setFinished();
            else
                setFailed();
        }
    } else if (child->isChangeable()) {
        if (isCurrentChild("盾拾い")) {
            if (!_70.hasProc()) {
                if (sub_71003BC058(false)) {
                    auto* weapon = sead::DynamicCast<act::Weapon>(_70.getProc(nullptr, nullptr));
                    child->sub_710039D2D0(weapon, "TargetWeapon",
                                         &ksys::act::ai::ParamPack::getActor);
                } else {
                    normal = true;
                }
            }
        } else if (_80) {
            auto* actor = mActor;
            auto* target = sub_71005D9050(actor);
            if ((!target || !target->hasProc() ||
                 !sub_710073033C(actor, target, *mParams.mNoShieldSearchDist_s)) &&
                sub_71003BC058(true))
                pick_up_shield = true;
        }
    }
    if (pick_up_shield) {
        changeToPickUpShield();
    } else if (normal) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mParams.mTargetPos_d, "TargetPos", -1);
        changeChild("通常", &pack);
    }
}

void EnemyShieldSearchOrBattle::loadParams_() {
    getStaticParam(&mParams.mShieldIdx_s, "ShieldIdx");
    getStaticParam(&mParams.mSearchShieldDist_s, "SearchShieldDist");
    getStaticParam(&mParams.mNoShieldSearchDist_s, "NoShieldSearchDist");
    getStaticParam(&mParams.mNoShieldTargetNearDist_s, "NoShieldTargetNearDist");
    getStaticParam(&mParams.mShieldReachDist_s, "ShieldReachDist");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
    getStaticParam(&mParams.mNoShieldEquipWpIdx_s, "NoShieldEquipWpIdx");
}

}  // namespace uking::ai
