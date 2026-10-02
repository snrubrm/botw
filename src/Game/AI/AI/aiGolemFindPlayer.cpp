#include "Game/AI/AI/aiGolemFindPlayer.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

GolemFindPlayer::GolemFindPlayer(const InitArg& arg) : LargeEnemyFindPlayer(arg) {}

GolemFindPlayer::~GolemFindPlayer() = default;

bool GolemFindPlayer::init_(sead::Heap* heap) {
    return LargeEnemyFindPlayer::init_(heap);
}

void GolemFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    LargeEnemyFindPlayer::enter_(params);
}

void GolemFindPlayer::leave_() {
    LargeEnemyFindPlayer::leave_();
}

void GolemFindPlayer::loadParams_() {
    LargeEnemyFindPlayer::loadParams_();
    getStaticParam(&mSearchExplosiveDist_s, "SearchExplosiveDist");
}

// NON_MATCHING: the original loads mActor for the first argument after the call
void GolemFindPlayer::m47() {
    sub_71005DB068(mActor, sub_71005D9330(mActor));
}

void GolemFindPlayer::calc_() {
    LargeEnemyFindPlayer::calc_();

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed() || !child->isChangeable())
        return;
    if (!isCurrentChild("戦闘") && !isCurrentChild("威嚇"))
        return;

    ksys::act::acc::PlayerBase player;
    ksys::act::acquireActor(&sub_71005D94AC(mActor), &player);
    if (player.m205())
        return;
    if (!sub_71005DE7F4(mActor, *mSearchExplosiveDist_s, 999.0f, sead::Mathf::pi(), true).hasProc())
        return;
    auto* actor = mActor;
    if (sub_710072E154(actor, sub_71005D9330(actor), nullptr, -1))
        m41();
}

}  // namespace uking::ai
