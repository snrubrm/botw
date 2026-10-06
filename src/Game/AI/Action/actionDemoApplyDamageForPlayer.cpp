#include "Game/AI/Action/actionDemoApplyDamageForPlayer.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::action {

DemoApplyDamageForPlayer::DemoApplyDamageForPlayer(const InitArg& arg)
    : ApplyDamageForPlayer(arg) {}

DemoApplyDamageForPlayer::~DemoApplyDamageForPlayer() = default;

bool DemoApplyDamageForPlayer::init_(sead::Heap* heap) {
    return ApplyDamageForPlayer::init_(heap);
}

bool DemoApplyDamageForPlayer::oneShot_() {
    if (!ApplyDamageForPlayer::oneShot_())
        return false;

    auto* info = ksys::act::PlayerInfo::instance();
    if (!info)
        return false;
    auto* player = info->mPlayerActor;
    if (!player)
        return false;

    const s32* life_ptr = mActor->getLife();
    const s32 life = life_ptr ? *life_ptr : 1;
    if (life > s32(info->getMaxHeartValue()))
        player->m324(life - s32(info->getMaxHeartValue()));
    else
        player->m324(0);
    return true;
}

void DemoApplyDamageForPlayer::loadParams_() {
    ApplyDamageForPlayer::loadParams_();
}

}  // namespace uking::action
