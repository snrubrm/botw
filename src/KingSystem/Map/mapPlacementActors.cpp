#include "KingSystem/Map/mapPlacementActors.h"
#include <prim/seadMemUtil.h>
#include <time/seadTickTime.h>
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Map/mapPlacementTree.h"

namespace ksys::map {

void PlacementActors::removeInnerData1() {
    _e8 = 0;
}

void PlacementActors::clearActorDataAndObjects() {
    for (int i = 0; i < mActorData.size(); ++i)
        deleteActorData(&mActorData[i]);
    if (mObjs)
        mObjs->freeObjects();
    _f8.fill(0);
}

// NON_MATCHING: an extra `and w0, w0, #1` on the returned bool
bool PlacementActors::checkResLoadStartedAndFailed() {
    bool result = false;
    for (int i = 0; !result && i < mActorData.size(); ++i)
        result = mActorData[i].mRes.requestedLoad();
    return result;
}

void PlacementActors::freeObjects() {
    if (mObjs)
        mObjs->freeObjects();
}

void PlacementActors::reinitActorDataEntryForTreeBuild() {
    for (int i = 0; i < int(mActorDataMapSize); ++i)
        initActorDataEntry(&mActorData[i], mActorData[i].mActorName.cstr());
}

u32 PlacementActors::getStaticNumInUse() const {
    return mObjs->mGroups[0].num_objs;
}

void PlacementActors::rebuildTree(PlacementTree* tree) {
    sead::TickTime start;
    tree->mLock.writeLock();
    tree->resetPlacementObjPtrs();
    mObjs->x_0(tree);
    tree->mLock.writeUnlock();
    static_cast<void>(start.diffToNow());

    PlacementMgr::instance()->mFlags.reset(PlacementMgr::MgrFlag::_20000);
    PlacementMgr::instance()->mFlags.set(PlacementMgr::MgrFlag::_1);
}

int PlacementActors::getNumGroups() const {
    return mObjs->mGroups.size();
}

bool PlacementActors::sub_7100D524B4() const {
    for (int i = 0; i < mActorData.size(); ++i) {
        if (mActorData[i]._b == 1)
            return true;
    }
    return false;
}

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

f32 getActorTraverseDistPlus100(const sead::SafeString& name, f32 a2) {
    return getActorTraverseDist(name, a2) + 100.0f;
}

}  // namespace ksys::map
