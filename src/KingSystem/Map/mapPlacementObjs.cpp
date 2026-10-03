#include "KingSystem/Map/mapPlacementActors.h"

namespace ksys::map {

int PlacementObjs::allocGroupForDynamicMap(PlacementMap* pmap) {
    for (int i = 0; i < 9; ++i) {
        auto& group = mGroups[i + 1];
        if (!group.map) {
            group.map = pmap;
            return i + 1;
        }
    }
    return -1;
}

void PlacementObjs::resetGroup(int group_idx) {
    mGroups[group_idx].map = nullptr;
    mGroups[group_idx].num_objs = 0;
}

}  // namespace ksys::map
