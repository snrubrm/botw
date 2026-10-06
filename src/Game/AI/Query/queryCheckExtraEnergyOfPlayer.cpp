#include "Game/AI/Query/queryCheckExtraEnergyOfPlayer.h"
#include <evfl/Query.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"

namespace uking::query {

CheckExtraEnergyOfPlayer::CheckExtraEnergyOfPlayer(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckExtraEnergyOfPlayer::~CheckExtraEnergyOfPlayer() = default;

int CheckExtraEnergyOfPlayer::doQuery() {
    s32 result;
    {
        ksys::act::acc::PlayerBase accessor;
        accessor.getPlayerFromPlayerInfo();
        if (!accessor.hasProc()) {
            result = 0;
        } else {
            const s32 energy = accessor.m322();
            s32 units = energy / 200;
            if (energy % 200 > 0)
                ++units;
            if (units > *mThreshold)
                result = 2;
            else
                result = units >= *mThreshold;
        }
    }
    return result;
}

void CheckExtraEnergyOfPlayer::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Threshold");
}

void CheckExtraEnergyOfPlayer::loadParams() {
    getDynamicParam(&mThreshold, "Threshold");
}

}  // namespace uking::query
