#include "KingSystem/Map/mapPlacementActors.h"
#include <algorithm>
#include <prim/seadMemUtil.h>
#include <time/seadTickTime.h>
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
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
    for (auto*& slot : _f8)
        slot = nullptr;
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

void PlacementActors::sub_7100D52C0C() {}

void PlacementActors::x_7() {
    _2a8078.lock();
    for (auto& obj : _2a8060)
        obj.sub_7100D4DB08();
    _2a8078.unlock();
}

void PlacementActors::x_9() {
    mMutex.lock();
    for (auto*& slot : _f8) {
        auto* obj = slot;
        if (!obj)
            continue;
        if (!obj->shouldSkipSpawn()) {
            if (obj->getFlags0().isOn(Object::Flag0::_1))
                PlacementMgr::instance()->enableObjStaticCompound(obj);
            PlacementMgr::instance()->sub_71011E9C28(obj, true);
        }
        slot = nullptr;
    }
    mMutex.unlock();
}

void PlacementActors::placeObject(Object* obj) {
    if (obj->mProc || obj->mFlags0.isOn(Object::Flag0::_4))
        obj->spawnGenGroupActorsIfNeeded(nullptr);

    if (obj->shouldSkipSpawn()) {
        PlacementMgr::instance()->disableObjStaticCompound(obj);
        PlacementMgr::instance()->sub_71011E9C28(obj, false);
    }

    if (obj->mActorFlags8.isOn(ActorFlag8::CanGetPouch) && obj->getForSaleLink())
        obj->mActorFlags8.reset(ActorFlag8::CanGetPouch);

    if (obj->mLinkData && (obj->mLinkData->findLinkWithType(MapLinkDefType::BasicSig) ||
                           obj->mLinkData->findLinkWithType(MapLinkDefType::BasicSigOnOnly))) {
        obj->setFieldATrue();
    }

    if (act::InfoData::instance()->hasTag(obj->getUnitConfigName(), 0xD53A8775) && obj->mLinkData &&
        obj->mLinkData->mLinksToSelf.findLinkWithType(MapLinkDefType::BasicSig)) {
        obj->mFlags.set(Object::Flag::IsTurnActorBowChargeAndHasBasicSigLink);
    }
}

// NON_MATCHING: only the loop bound (`cmp x9, #0x80; b.lt` in the original, `cmp x9, #0x7f; b.le` here: clang canonicalises
// the exit test)
void PlacementActors::sub_7100D52CA4(Object* obj) {
    mMutex.lock();
    for (int i = 0; i < 128; i += 2) {
        if (!_f8[i]) {
            _f8[i] = obj;
            break;
        }
        if (!_f8[i + 1]) {
            _f8[i + 1] = obj;
            break;
        }
    }
    mMutex.unlock();
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

namespace {
// 0x7101ec0b8c / 0x7101ec0c04 (indexed by the integer part of the bounding size, clamped to the last entry)
constexpr f32 sPassiveTraverseDist[30] = {80.0f, 100.0f, 130.0f, 154.0f, 169.0f, 184.0f, 215.0f, 246.0f, 277.0f, 308.0f, 354.0f, 400.0f, 446.0f, 492.0f, 539.0f, 600.0f, 650.0f, 700.0f, 750.0f, 800.0f, 850.0f, 900.0f, 950.0f, 1000.0f, 1050.0f, 1100.0f, 1300.0f, 1400.0f, 1500.0f, 1600.0f};
constexpr f32 sTraverseDist[15] = {70.0f, 80.0f, 90.0f, 100.0f, 110.0f, 120.0f, 140.0f, 160.0f, 180.0f, 200.0f, 230.0f, 260.0f, 290.0f, 320.0f, 350.0f};
}  // namespace

f32 getActorTraverseDist(const sead::SafeString& name, f32 a2) {
    f32 dist = act::InfoData::instance()->getTraverseDist(name.cstr());
    if (dist > 0.0f) {
        const char* profile;
        act::InfoData::instance()->getActorProfile(&profile, name.cstr());
        const sead::SafeString profile_str(profile);
        if (profile_str.findIndex("Enemy") != -1 || profile_str.findIndex("NPC") != -1)
            dist *= 0.7f;
        return dist;
    }

    f32 size = act::InfoData::instance()->getBoundingForTraverse(name.cstr());
    if (size <= 0.0f)
        size = a2;

    const char* profile;
    act::InfoData::instance()->getActorProfile(&profile, name.cstr());
    const sead::SafeString profile_str(profile);
    if (profile_str.findIndex("Passive") != -1) {
        if (size < 0.3f)
            return 30.0f;
        if (size < 0.5f)
            return 50.0f;
        return sPassiveTraverseDist[std::min(s32(size), 29)];
    }

    if (size < 0.3f)
        return 40.0f;
    if (size < 0.5f)
        return 45.0f;
    if (size < 0.8f)
        return 50.0f;
    return sTraverseDist[std::min(s32(size), 14)] * 0.8f;
}

f32 getActorTraverseDistPlus100(const sead::SafeString& name, f32 a2) {
    return getActorTraverseDist(name, a2) + 100.0f;
}

}  // namespace ksys::map
