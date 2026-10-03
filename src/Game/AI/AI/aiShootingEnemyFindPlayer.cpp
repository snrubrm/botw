#include "Game/AI/AI/aiShootingEnemyFindPlayer.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"

namespace uking::ai {

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
    getStaticParam(&mParams.mReHideTime_s, "ReHideTime");
    getStaticParam(&mParams.mExplosivesAvoidDist_s, "ExplosivesAvoidDist");
    getStaticParam(&mParams.mExplosivesAvoidSpeed_s, "ExplosivesAvoidSpeed");
    getStaticParam(&mParams.mExplosivesAvoidAng_s, "ExplosivesAvoidAng");
    getStaticParam(&mParams.mHideStartDistMin_s, "HideStartDistMin");
    getStaticParam(&mParams.mHideStartDistMax_s, "HideStartDistMax");
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
