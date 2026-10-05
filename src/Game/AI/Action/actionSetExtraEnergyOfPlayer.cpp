#include "Game/AI/Action/actionSetExtraEnergyOfPlayer.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"

// 0x7100947444: source namespace is unknown; follows existing global consumer declarations.
void sub_7100947444(f32 value);

namespace uking::action {

SetExtraEnergyOfPlayer::SetExtraEnergyOfPlayer(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetExtraEnergyOfPlayer::~SetExtraEnergyOfPlayer() = default;

bool SetExtraEnergyOfPlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetExtraEnergyOfPlayer::loadParams_() {
    getDynamicParam(&mValue_d, "Value");
    getDynamicParam(&mProcessingMode_d, "ProcessingMode");
}

bool SetExtraEnergyOfPlayer::oneShot_() {
    ksys::act::acc::PlayerBase player;
    player.getPlayerFromPlayerInfo();
    if (player.hasProc()) {
        sub_7100947444(player.m322());
        const f32 previous = *mProcessingMode_d == 1 ? player.m322() : 0.f;
        player.setExtraEnergy(previous + *mValue_d * 200.f);
        player.x_2();
        player.x_3();
    }
    return true;
}

}  // namespace uking::action
