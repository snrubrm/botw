#include "Game/AI/AI/aiHorseRideEnemyBattle.h"
#include "KingSystem/ActorSystem/actActor.h"
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
