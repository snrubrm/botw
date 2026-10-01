#include "KingSystem/Map/mapPlacementActors.h"
#include "KingSystem/Map/mapObject.h"

namespace ksys::map {

Object* PlacementActors::getObj(int group_idx, int object_idx) {
    return &mObjs->mGroups[group_idx].objects[object_idx];
}

Object* PlacementActors::getStaticObj_2(s32 idx) const {
    return &mObjs->mGroups[0].objects[idx];
}

Object* PlacementActors::getStaticObj_0(int object_idx) {
    return &mObjs->mGroups[0].objects[object_idx];
}

Object* PlacementActors::getStaticObj(int object_idx) {
    return &mObjs->mGroups[0].objects[object_idx];
}

int PlacementActors::getNumObjs(int group_idx) const {
    return mObjs->mGroups[group_idx].num_objs;
}

PlacementMap* PlacementActors::getMapNextGroup(int group_idx) const {
    return mObjs->mGroups[group_idx].map;
}

u32 PlacementActors::getNumStaticObjs() const {
    return mObjs->mGroups[0].num_objs;
}

void PlacementActors::setNumInUseForStaticGroup(int num) {
    mObjs->mGroups[0].num_objs = num;
}

Object* PlacementActors::getStaticObj_1(int object_idx) {
    return &mObjs->mGroups[0].objects[object_idx];
}

u32 PlacementActors::allocGroupForDynamicMap(PlacementMap* pmap) {
    return mObjs->allocGroupForDynamicMap(pmap);
}

void PlacementActors::resetGroup(int group_idx) {
    mObjs->resetGroup(group_idx);
}

}  // namespace ksys::map
