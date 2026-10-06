#include "Game/AI/Query/queryCheckDistanceFromPlayer.h"
#include <evfl/Query.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"

namespace uking::query {

CheckDistanceFromPlayer::CheckDistanceFromPlayer(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckDistanceFromPlayer::~CheckDistanceFromPlayer() = default;

// NON_MATCHING: same logic; the original multiplies border * border after the distance sum and
// compares with `pl` (ours hoists the multiply and compares with `ge`).
int CheckDistanceFromPlayer::doQuery() {
    if (!mActor)
        return 0;
    const f32 border = *mBorder;
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    sead::Vector3f player_pos;
    {
        ksys::act::acc::PlayerBase accessor;
        accessor.getPlayerFromPlayerInfo();
        if (!accessor.hasProc())
            return 0;
        player_pos = accessor.getActorMtx().getTranslation();
    }
    const sead::Vector3f diff = pos - player_pos;
    return diff.x * diff.x + diff.y * diff.y + diff.z * diff.z >= border * border;
}

void CheckDistanceFromPlayer::loadParams(const evfl::QueryArg& arg) {
    loadFloat(arg.param_accessor, "Border");
}

void CheckDistanceFromPlayer::loadParams() {
    getDynamicParam(&mBorder, "Border");
}

}  // namespace uking::query
