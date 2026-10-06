#include "Game/AI/AI/aiShootingEnemyFindPlayer.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
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

// 0x710056aa30
void ShootingEnemyFindPlayer::sub_710056AA30() {
    ksys::act::ai::InlineParamPack pack;
    const sead::Vector3f pos = sub_71005D9330(mActor);
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("隠れる", &pack);
}

// 0x710056ab10
void ShootingEnemyFindPlayer::sub_710056AB10() {
    ksys::act::ai::InlineParamPack pack;
    const sead::Vector3f pos = sub_71005D9330(mActor);
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("隠れられない", &pack);
}

// NON_MATCHING: instruction scheduling only (the third static-param load is hoisted above the fadd)
// 0x710056abf0
bool ShootingEnemyFindPlayer::sub_710056ABF0() {
    if (isCurrentChild("危険回避"))
        return false;
    _180.reset();
    auto& link = sub_71005DE7F4(mActor, *mParams.mExplosivesAvoidDist_s + 5.0f,
                                *mParams.mExplosivesAvoidSpeed_s, *mParams.mExplosivesAvoidAng_s, true);
    if (!link.hasProc())
        return false;
    _180 = link;
    sub_710056AD84();
    return true;
}

// 0x710056ad84
void ShootingEnemyFindPlayer::sub_710056AD84() {
    if (!_180.hasProc())
        return;
    ksys::act::ai::InlineParamPack pack;
    const sead::Vector3f pos = sub_7100736A24(&_180);
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("危険回避", &pack);
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
