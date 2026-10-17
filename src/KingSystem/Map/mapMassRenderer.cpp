#include "KingSystem/Map/mapPlacementMgr.h"
#include <gsys/gsysModelUnit.h>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnitDrawArray.h>
#include <prim/seadScopedLock.h>
#include "KingSystem/Map/mapPlacementActors.h"

namespace ksys::map {

void MassRenderer::beginCleanup() {
    mCleanupIndex = 0;
    mUnits.freeBuffer();
}

bool MassRenderer::cleanupModel() {
    if (mSlots[mCleanupIndex].mModel) {
        gsys::Model::sub_7100BF69F8(mSlots[mCleanupIndex].mModel);
        mSlots[mCleanupIndex].mModel = nullptr;
    }
    return ++mCleanupIndex == 3;
}

void MassRenderer::sub_71011E4090(PlacementMgr* mgr, bool a) {
    auto lock = sead::makeScopedLock(_210);
    auto lock2 = sead::makeScopedLock(_38);
    const u32 num = _18.size();
    for (u32 i = 0; i < num; ++i) {
        const auto* entry = _18[i];
        if (!entry->_6)
            continue;
        auto* unit = mgr->mPlacementActors->mActorData[entry->mActorDataIdx]._10;
        if (!unit)
            continue;
        auto* draw_array = unit->getDrawArray();
        if (!draw_array)
            continue;
        const u32 size = draw_array->_18;
        for (u32 j = 0; j < size; ++j)
            draw_array->flushUBO(j);
    }
}

bool MassRenderer::sub_71011E41F4(const void* p) const {
    for (const auto& slot : mSlots) {
        if (slot.mModel == p)
            return true;
    }
    return false;
}

}  // namespace ksys::map
