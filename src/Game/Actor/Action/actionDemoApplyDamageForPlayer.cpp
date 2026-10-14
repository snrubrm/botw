#include "Game/Actor/Action/actionDemoApplyDamageForPlayer.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/Player/actPlayerInfo.h"

namespace uking::action {

DemoApplyDamageForPlayer::DemoApplyDamageForPlayer(const InitArg& arg)
    : DemoApplyDamageBase(arg) {}

DemoApplyDamageForPlayer::~DemoApplyDamageForPlayer() = default;

bool DemoApplyDamageForPlayer::init_(sead::Heap* heap) {
    return DemoApplyDamageBase::init_(heap);
}

bool DemoApplyDamageForPlayer::oneShot_() {
    if (!DemoApplyDamageBase::oneShot_())
        return false;

    auto* info = uking::act::PlayerInfo::instance();
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
    DemoApplyDamageBase::loadParams_();
}

}  // namespace uking::action
