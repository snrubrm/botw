#include "Game/AI/AI/aiMimicEnemyFindPlayer.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

MimicEnemyFindPlayer::MimicEnemyFindPlayer(const InitArg& arg) : EnemyBaseFindPlayer(arg) {}

MimicEnemyFindPlayer::~MimicEnemyFindPlayer() = default;

void MimicEnemyFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBaseFindPlayer::enter_(params);
}

bool MimicEnemyFindPlayer::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void MimicEnemyFindPlayer::leave_() {
    EnemyBaseFindPlayer::leave_();
    sub_71005DB3EC(mActor);
}

void MimicEnemyFindPlayer::loadParams_() {
    EnemyBaseFindPlayer::loadParams_();
    getStaticParam(&mPlayerForceFindDist_s, "PlayerForceFindDist");
    getAITreeVariable(&mMimicryMaterial_a, "MimicryMaterial");
    getAITreeVariable(&mIsStartResetMimicry_a, "IsStartResetMimicry");
}

}  // namespace uking::ai
