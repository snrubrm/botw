#include "Game/AI/AI/aiMimicEnemyFindPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
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

bool MimicEnemyFindPlayer::isFinished() const {
    if (ActionBase::isFinished())
        return true;
    if (isCurrentChild("戦闘"))
        return getCurrentChild()->isFinished();
    return false;
}

bool MimicEnemyFindPlayer::m35() {
    const auto& player_pos = sub_71005D9330(mActor);
    const auto& mtx = mActor->getMtx();
    const sead::Vector2f player_xz(player_pos.x, player_pos.z);
    const sead::Vector2f actor_xz(mtx(0, 3), mtx(2, 3));
    if ((player_xz - actor_xz).length() <= *mPlayerForceFindDist_s)
        return true;
    return EnemyBaseFindPlayer::m35();
}

}  // namespace uking::ai
