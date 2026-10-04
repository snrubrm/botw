#include "KingSystem/Map/mapPlacementActors.h"
#include "KingSystem/Map/mapObject.h"

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

void PlacementObjs::freeObjects() {
    for (s32 group_idx = 0; group_idx < 10; ++group_idx) {
        auto& group = mGroups(group_idx);
        for (s32 i = 0; i < group.num_objs; ++i)
            group.objects[i].free();
    }
}

}  // namespace ksys::map
