#include "KingSystem/Map/mapPlacementMapMgr.h"
#include "KingSystem/Map/mapMapProperties.h"

namespace ksys::map {

PlacementMap* PlacementMapMgr::getMap(int idx) {
    return &mMaps[idx];
}

// NON_MATCHING: the original compares `pz <= 7999` first and places the `return x` block before the index
// computation; ours tests `px` first (instcombine orders the two compares by definition order).
bool PlacementMapMgr::isHkscResStatus3(const sead::Vector3f& pos, bool x) {
    int col, row;
    if (mMapProps->m0() == 1 || mMapProps->m0() == 2) {
        row = 4;
        col = 5;
    } else {
        const int px = int(pos.x) + 5000;
        const int pz = int(pos.z) + 4000;
        if (!(pz <= 7999 && px <= 9999))
            return x;
        col = px / 1000;
        row = pz / 1000;
        if ((col | row) < 0)
            return x;
    }
    return mMaps[u8(row + col * 8)].isDynamicLoaded(pos);
}

}  // namespace ksys::map
