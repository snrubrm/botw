#include "Game/AI/AI/aiShootingEnemyFindPlayer.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"

namespace uking::ai {

// NON_MATCHING: scheduling of the first two stores
ShootingEnemyFindPlayer::ShootingEnemyFindPlayer(const InitArg& arg)
    : SimpleShootingEnemyFindPlayer(arg) {}

ShootingEnemyFindPlayer::~ShootingEnemyFindPlayer() = default;

bool ShootingEnemyFindPlayer::init_(sead::Heap* heap) {
    return SimpleShootingEnemyFindPlayer::init_(heap);
}

void ShootingEnemyFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    SimpleShootingEnemyFindPlayer::enter_(params);
    _190 = ksys::Timer(0, 0);
}

void ShootingEnemyFindPlayer::leave_() {
    SimpleShootingEnemyFindPlayer::leave_();
}

void ShootingEnemyFindPlayer::loadParams_() {
    SimpleShootingEnemyFindPlayer::loadParams_();
    getStaticParam(&mReHideTime_s, "ReHideTime");
    getStaticParam(&mExplosivesAvoidDist_s, "ExplosivesAvoidDist");
    getStaticParam(&mExplosivesAvoidSpeed_s, "ExplosivesAvoidSpeed");
    getStaticParam(&mExplosivesAvoidAng_s, "ExplosivesAvoidAng");
    getStaticParam(&mHideStartDistMin_s, "HideStartDistMin");
    getStaticParam(&mHideStartDistMax_s, "HideStartDistMax");
}

bool ShootingEnemyFindPlayer::m45() {
    return isCurrentChild("威嚇") && m46();
}

bool ShootingEnemyFindPlayer::m46() {
    auto* actor = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor);
    if (!actor)
        return false;
    const int weapon_idx = *mWeaponIdx_s;
    auto* weapon =
        sead::DynamicCast<uking::act::Weapon>(actor->getWeapons()->getEquippedWeapon(weapon_idx));
    if (!weapon || !weapon->isWeaponType3())
        return true;
    if (weapon->_d54 == 1 || weapon->_d54 == 2)
        return false;
    return (weapon->_af8._0 | 1) != 7;
}

}  // namespace uking::ai
