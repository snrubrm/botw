#include "Game/AI/AI/aiEnemyShieldSearchOrBattle.h"
#include "Game/Actor/actEnemy.h"
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
