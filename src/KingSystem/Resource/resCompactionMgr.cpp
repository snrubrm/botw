#include "KingSystem/Resource/resCompactionMgr.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/Graphics/gfxForestRenderer.h"
#include "KingSystem/Map/mapPlacementMapMgr.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Map/mapStagePreActorCache.h"
#include "KingSystem/Resource/resResourceMgrTask.h"

namespace ksys::res {

CompactionMgr::CompactionMgr() = default;

CompactionMgr::~CompactionMgr() {
    if (_18) {
        ResourceMgrTask::instance()->setCompactionStopped(true);
        _18 = false;
    }
}

bool CompactionMgr::init(const InitArg& arg) {
    return true;
}

// NON_MATCHING: the original speculates the last two loading checks (cset+orr) and groups
// (initializing || loading_maps) / (forest_busy || pause) differently; same logic
void CompactionMgr::stopCompactionIfTooLong(const CalcArg& arg) {
    const bool initializing = act::BaseProcMgr::instance() &&
                              act::BaseProcMgr::instance()->isAnyInitializerThreadActive();

    bool loading_maps = false;
    auto* placement_mgr = map::PlacementMgr::instance();
    if (placement_mgr && placement_mgr->mPlacementMapMgr) {
        auto* map_mgr = placement_mgr->mPlacementMapMgr;
        loading_maps = map_mgr->mNeedLoadDynMap > 0 || map_mgr->mNeedLoadDynMapPhysics > 0 ||
                       placement_mgr->mLoadActorNumTotal > placement_mgr->mPreActorNumDone;
    }

    bool forest_busy = false;
    auto* cache = map::StagePreActorCache::instance();
    if (cache) {
        auto* forest = cache->getForestRenderer();
        if (forest && forest->x_9())
            forest_busy = forest->_54 != 15;
    }

    const bool pause = arg.pause_compaction;

    if (_18 && _8.diffToNow().toMilliSeconds() > 100) {
        ResourceMgrTask::instance()->setCompactionStopped(true);
        _18 = false;
    }

    sead::TickTime now;
    if (initializing || loading_maps || forest_busy || pause) {
        _10 = now;
        ResourceMgrTask::instance()->x(false);
    } else if (now.diff(_10).toMilliSeconds() > 100) {
        ResourceMgrTask::instance()->x(true);
    }
}

}  // namespace ksys::res
