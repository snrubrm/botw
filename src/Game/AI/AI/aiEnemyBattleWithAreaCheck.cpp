#include "Game/AI/AI/aiEnemyBattleWithAreaCheck.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

EnemyBattleWithAreaCheck::EnemyBattleWithAreaCheck(const InitArg& arg) : EnemyBattle(arg) {}

EnemyBattleWithAreaCheck::~EnemyBattleWithAreaCheck() = default;

bool EnemyBattleWithAreaCheck::init_(sead::Heap* heap) {
    return EnemyBattle::init_(heap);
}

void EnemyBattleWithAreaCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
}

void EnemyBattleWithAreaCheck::calc_() {
    EnemyBattle::calc_();
}

void EnemyBattleWithAreaCheck::leave_() {
    EnemyBattle::leave_();
}

void EnemyBattleWithAreaCheck::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mAttackVMin_s, "AttackVMin");
    getStaticParam(&mAttackVMax_s, "AttackVMax");
    getStaticParam(&mAttackFar_s, "AttackFar");
}

// NON_MATCHING: regalloc (pos.x and pos.z swap s8/s9)
bool EnemyBattleWithAreaCheck::m40() {
    if (!EnemyBattle::m40())
        return false;

    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    const auto& target_pos = sub_71005D9330(mActor);
    const f32 dy = target_pos.y - pos.y;
    if (*mAttackVMin_s <= dy && dy <= *mAttackVMax_s) {
        const f32 radius = *mAttackFar_s + sub_71007320F0(mActor, *mWeaponIdx_s);
        return ksys::util::sqXZDistance(target_pos, pos) <= radius * radius;
    }
    return false;
}

}  // namespace uking::ai
