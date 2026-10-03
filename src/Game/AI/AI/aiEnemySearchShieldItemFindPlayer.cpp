#include "Game/AI/AI/aiEnemySearchShieldItemFindPlayer.h"

namespace uking::ai {

EnemySearchShieldItemFindPlayer::EnemySearchShieldItemFindPlayer(const InitArg& arg)
    : LandHumEnemyFindPlayer(arg) {}

EnemySearchShieldItemFindPlayer::~EnemySearchShieldItemFindPlayer() = default;

bool EnemySearchShieldItemFindPlayer::init_(sead::Heap* heap) {
    return LandHumEnemyFindPlayer::init_(heap);
}

void EnemySearchShieldItemFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    LandHumEnemyFindPlayer::enter_(params);
}

void EnemySearchShieldItemFindPlayer::leave_() {
    LandHumEnemyFindPlayer::leave_();
}

void EnemySearchShieldItemFindPlayer::loadParams_() {
    LandHumEnemyFindPlayer::loadParams_();
    getStaticParam(&mParams.mShieldIdx_s, "ShieldIdx");
    getStaticParam(&mParams.mSearchShieldDist_s, "SearchShieldDist");
    getStaticParam(&mParams.mNoShieldSearchDist_s, "NoShieldSearchDist");
    getStaticParam(&mParams.mSearchObjectDist_s, "SearchObjectDist");
    getStaticParam(&mParams.mItemChaseableSpd_s, "ItemChaseableSpd");
    getStaticParam(&mParams.mItemChasealeRot_s, "ItemChasealeRot");
    getStaticParam(&mParams.mCanGrabHeavy_s, "CanGrabHeavy");
}

}  // namespace uking::ai
