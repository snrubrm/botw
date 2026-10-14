#include "Game/Actor/AI/aiGolemFindPlayer.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/aiUnk_71005D6D10.h"

namespace uking::ai {

GolemFindPlayer::GolemFindPlayer(const InitArg& arg) : GiantEnemyFindPlayer(arg) {}

GolemFindPlayer::~GolemFindPlayer() = default;

bool GolemFindPlayer::init_(sead::Heap* heap) {
    return GiantEnemyFindPlayer::init_(heap);
}

void GolemFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    GiantEnemyFindPlayer::enter_(params);
}

void GolemFindPlayer::leave_() {
    GiantEnemyFindPlayer::leave_();
}

void GolemFindPlayer::loadParams_() {
    GiantEnemyFindPlayer::loadParams_();
    getStaticParam(&mSearchExplosiveDist_s, "SearchExplosiveDist");
}

void GolemFindPlayer::m47() {
    const auto& pos = sub_71005D9330(mActor);
    sub_71005DB068(mActor, pos);
}

void GolemFindPlayer::calc_() {
    GiantEnemyFindPlayer::calc_();

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
