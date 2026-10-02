#include "Game/AI/AI/aiShootingEnemyFindPlayer.h"

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

}  // namespace uking::ai
