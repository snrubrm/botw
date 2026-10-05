#include "Game/AI/Action/actionSetExtraLifeOfPlayer.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"

namespace uking::action {

SetExtraLifeOfPlayer::SetExtraLifeOfPlayer(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetExtraLifeOfPlayer::~SetExtraLifeOfPlayer() = default;

bool SetExtraLifeOfPlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetExtraLifeOfPlayer::loadParams_() {
    getDynamicParam(&mValue_d, "Value");
    getDynamicParam(&mProcessingMode_d, "ProcessingMode");
}

bool SetExtraLifeOfPlayer::oneShot_() {
    ksys::act::acc::PlayerBase player;
    player.getPlayerFromPlayerInfo();
    if (player.hasProc()) {
        s32 value = *mValue_d;
        if (*mProcessingMode_d == 1)
            value += player.m321();
        player.setExtraLife(value);
        player.x_2();
        player.x_4();
        ui::sub_7100A94AF0();
    }
    return true;
}

}  // namespace uking::action
