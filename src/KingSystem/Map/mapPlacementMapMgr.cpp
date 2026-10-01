#include "KingSystem/Map/mapPlacementMapMgr.h"

namespace ksys::map {

PlacementMap* PlacementMapMgr::getMap(int idx) {
    return &mMaps[idx];
}

}  // namespace ksys::map
