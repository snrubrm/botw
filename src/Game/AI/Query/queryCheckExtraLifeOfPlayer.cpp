#include "Game/AI/Query/queryCheckExtraLifeOfPlayer.h"
#include <evfl/Query.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"

namespace uking::query {

CheckExtraLifeOfPlayer::CheckExtraLifeOfPlayer(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckExtraLifeOfPlayer::~CheckExtraLifeOfPlayer() = default;

int CheckExtraLifeOfPlayer::doQuery() {
    s32 result;
    {
        ksys::act::acc::PlayerBase accessor;
        accessor.getPlayerFromPlayerInfo();
        if (!accessor.hasProc()) {
            result = 0;
        } else if (accessor.m321() > *mThreshold) {
            result = 2;
        } else {
            result = accessor.m321() >= *mThreshold;
        }
    }
    return result;
}

void CheckExtraLifeOfPlayer::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Threshold");
}

void CheckExtraLifeOfPlayer::loadParams() {
    getDynamicParam(&mThreshold, "Threshold");
}

}  // namespace uking::query
