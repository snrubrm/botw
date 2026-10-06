#include "Game/AI/Query/queryCheckDistanceForWarp.h"
#include <evfl/Query.h>
#include <math/seadMathCalcCommon.h>
#include "Game/gameSceneMgr.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"

namespace uking::query {

CheckDistanceForWarp::CheckDistanceForWarp(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckDistanceForWarp::~CheckDistanceForWarp() = default;

int CheckDistanceForWarp::doQuery() {
    return m13();
}

// NON_MATCHING: stack layout (the original keeps the position and the accessor 8 bytes lower) and the order of the
// two address computations for the getMapPosition arguments.
bool CheckDistanceForWarp::m13() {
    auto* mgr = SceneMgr::instance();
    sead::Vector3f destination;
    if (!mgr || !mgr->getMapPosition(mWarpDestPosName, &destination, &mgr->mStageName, mWarpDestMapName))
        return true;

    ksys::act::acc::PlayerBase player;
    player.getPlayerFromPlayerInfo();
    if (!player.hasProc())
        return true;

    const auto& mtx = player.getActorMtx();
    const f32 dx = mtx(0, 3) - destination.x;
    const f32 dz = mtx(2, 3) - destination.z;
    return !(sead::Mathf::sqrt(dx * dx + dz * dz) < 500.0f);
}

void CheckDistanceForWarp::loadParams(const evfl::QueryArg& arg) {
    loadString(arg.param_accessor, "WarpDestMapName");
    loadString(arg.param_accessor, "WarpDestPosName");
}

void CheckDistanceForWarp::loadParams() {
    getDynamicParam(&mWarpDestMapName, "WarpDestMapName");
    getDynamicParam(&mWarpDestPosName, "WarpDestPosName");
}

}  // namespace uking::query
